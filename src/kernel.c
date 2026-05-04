#include "vga.h"
#include "stdint.h"
#include "gdt/gdt.h"
#include "interrupts/idt.h"
#include "timer.h"
#include "kmalloc.h"
#include "stdlib/stdio.h"
#include "keyboard.h"
#include "multiboot.h"
#include "memory.h"
#include "util.h"
#include "process.h"
#include "scheduler.h"
#include "shell.h"

void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info* bootInfo) {
    vgaInit();
    initGdt();
    initIdt();
    initMemory(bootInfo->mem_upper * 1024, 0x200000);
    kmallocInit(0x100000);
    schedulerInit();
    initKeyboard();
    shellInit();
    initTimer();
    for (;;) asm volatile("hlt");
}
