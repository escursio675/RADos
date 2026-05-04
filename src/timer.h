#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "interrupts/idt.h"

extern uint64_t ticks;

void initTimer();
void onIrq0(struct InterruptRegisters* regs);

#endif