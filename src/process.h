#ifndef PROCESS_H
#define PROCESS_H

#include "stdint.h"

#define MAX_PROCESSES     64
#define KERNEL_STACK_SIZE 4096

typedef enum {
    PROCESS_STATE_UNUSED = 0,
    PROCESS_STATE_READY,
    PROCESS_STATE_RUNNING,
    PROCESS_STATE_BLOCKED,
    PROCESS_STATE_DEAD
} ProcessState;

typedef struct {
    uint32_t edi, esi, ebx, ebp;
    uint32_t eip;
} CPUContext;

typedef struct Process {
    uint32_t     pid;
    ProcessState state;
    CPUContext   context;
    uint32_t     esp;
    uint8_t*     kernelStack;
    uint32_t     timeSlice;
} Process;

extern Process  processList[MAX_PROCESSES];
extern Process* currentProcess;

void     processInit(void);
Process* processCreate(void (*entry)(void));
void     processExit(void);

#endif