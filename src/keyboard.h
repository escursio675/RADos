#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "stdint.h"
#include "interrupts/idt.h"

void initKeyboard();
void keyboardHandler(struct InterruptRegisters* regs);

#endif