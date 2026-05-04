#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "../interrupts/idt.h"

void stopwatchInit(void);
int  stopwatchHandleKey(char c);
void stopwatchOnTick(void);

#endif