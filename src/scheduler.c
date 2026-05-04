#include "scheduler.h"
#include "process.h"
#include "stdlib/stdio.h"

static int currentIndex = -1;

void schedulerInit(void) {
    processInit();
}

// Pick next READY process in round-robin order
static Process* pickNext(void) {
    int count = 0;
    int i = (currentIndex + 1) % MAX_PROCESSES;

    while (count < MAX_PROCESSES) {
        if (processList[i].state == PROCESS_STATE_READY ||
            processList[i].state == PROCESS_STATE_RUNNING) {
            return &processList[i];
        }
        i = (i + 1) % MAX_PROCESSES;
        count++;
    }
    return 0; // nothing runnable
}

// Called from timer IRQ every tick
void schedulerTick(struct InterruptRegisters* regs) {
    if (currentProcess) {
        // Decrement time slice
        if (currentProcess->timeSlice > 0) {
            currentProcess->timeSlice--;
            if (currentProcess->timeSlice > 0) {
                return; // slice not exhausted yet
            }
        }
    }

    Process* next = pickNext();
    if (!next || next == currentProcess) {
        // Reset slice and keep running
        if (currentProcess) {
            currentProcess->timeSlice = 5;
        }
        return;
    }

    Process* prev = currentProcess;

    // Update states
    if (prev && prev->state == PROCESS_STATE_RUNNING) {
        prev->state    = PROCESS_STATE_READY;
        prev->timeSlice = 5;  // reset for next turn
    }

    next->state    = PROCESS_STATE_RUNNING;
    next->timeSlice = 5;
    currentProcess  = next;
    currentIndex    = (int)(next - processList);

    if (prev) {
        // Save prev->esp and load next->esp, then ret into next->entry
        contextSwitch(&prev->esp, next->esp);
    } else {
        // First ever switch — no previous context to save
        // Jump directly; use a dummy save location
        uint32_t dummy;
        contextSwitch(&dummy, next->esp);
    }
}

// Voluntarily give up the CPU (resets slice to 0 to force a switch)
void schedulerYield(void) {
    if (currentProcess) {
        currentProcess->timeSlice = 0;
    }
    // Trigger a software timer-style reschedule via a dummy tick
    schedulerTick(0);
}