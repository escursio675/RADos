#include "shutdown.h"
#include "vga.h"
#include "util.h"

void shutdownMachine(void) {
    Reset();
    print("  Shutting down...\n");

    // QEMU ACPI shutdown
    outPortB(0x604, 0x00);
    outPortB(0x604, 0x02);

    // Bochs shutdown
    outPortB(0x8900, 'S');
    outPortB(0x8900, 'h');
    outPortB(0x8900, 'u');
    outPortB(0x8900, 't');
    outPortB(0x8900, 'd');
    outPortB(0x8900, 'o');
    outPortB(0x8900, 'w');
    outPortB(0x8900, 'n');

    // Older QEMU/Bochs
    outPortB(0xB004, 0x00);
    outPortB(0xB004, 0x02);

    // Nothing worked — halt
    print("  Shutdown failed. CPU halted.\n");
    for (;;) asm volatile("cli; hlt");
}
