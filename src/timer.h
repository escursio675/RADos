#include "stdint.h"

void initTimer();
void onIrq0(struct InterruptRegisters *regs);
uint64_t getTicks();
uint32_t getFreq();