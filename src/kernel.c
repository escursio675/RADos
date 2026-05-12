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

#include "commands/help.h"
#include "commands/uptime.h"
#include "commands/clear.h"
#include "commands/greet.h"
#include "commands/hexdump.h"

void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info* bootInfo){
    initGdt();
    //print("GDT is done!\r\n");

    initIdt();
    initTimer();
    initKeyboard();

    //help();

    //printf("\n\nUptime: %lds", uptime());

    //greet();

    //clear();

    hexdump(bootInfo, 128);
    

    for(;;);
}
