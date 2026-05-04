#include "process.h"
#include "kmalloc.h"
#include "util.h"
#include "stdlib/stdio.h"

Process  processList[MAX_PROCESSES];
Process* currentProcess = 0;
static uint32_t nextPid = 1;

void processInit(void) {
    memset(processList, 0, sizeof(processList));
    currentProcess = 0;
}

/*
 * processCreate — sets up a new kernel-mode process.
 *
 * We carve out a kernel stack, then fake an initial stack frame
 * so that the first context switch lands at `entry`.
 *
 * Initial stack layout (high → low):
 *   [ entry ptr  ]   ← pushed as "return address" of contextSwitch
 *   [ 0          ]   ← dummy EBP
 *   [ 0          ]   ← dummy EBX
 *   [ 0          ]   ← dummy ESI
 *   [ 0          ]   ← dummy EDI
 *    ^-- esp points here (context.esp)
 */
Process* processCreate(void (*entry)(void)) {
    // Find a free slot
    Process* proc = 0;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processList[i].state == PROCESS_STATE_UNUSED) {
            proc = &processList[i];
            break;
        }
    }
    if (!proc) {
        printf("processCreate: no free slots!\n");
        return 0;
    }

    // Allocate kernel stack
    proc->kernelStack = (uint8_t*) kmalloc(KERNEL_STACK_SIZE);
    if (!proc->kernelStack) {
        printf("processCreate: kmalloc failed!\n");
        return 0;
    }
    memset(proc->kernelStack, 0, KERNEL_STACK_SIZE);

    // Stack grows downward; start at the top
    uint32_t* sp = (uint32_t*)(proc->kernelStack + KERNEL_STACK_SIZE);

    // Push entry as the "return address" that contextSwitch will ret into
    *(--sp) = (uint32_t) entry;

    // Push dummy saved-register values (edi, esi, ebx, ebp)
    *(--sp) = 0; // EBP
    *(--sp) = 0; // EBX
    *(--sp) = 0; // ESI
    *(--sp) = 0; // EDI

    proc->esp        = (uint32_t) sp;
    proc->pid        = nextPid++;
    proc->state      = PROCESS_STATE_READY;
    proc->timeSlice  = 5; // 5 timer ticks (~50ms at 100Hz)

    return proc;
}

// Called by a process to remove itself
void processExit(void) {
    if (currentProcess) {
        currentProcess->state = PROCESS_STATE_DEAD;
    }
    // Scheduler will skip DEAD processes; spin until next tick
    for (;;) asm volatile("hlt");
}