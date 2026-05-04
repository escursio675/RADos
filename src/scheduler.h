#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "stdint.h"
#include "process.h"
#include "interrupts/idt.h"

void schedulerInit(void);
void schedulerTick(struct InterruptRegisters* regs);
void schedulerYield(void);

extern void contextSwitch(uint32_t* oldEsp, uint32_t newEsp);

#endif