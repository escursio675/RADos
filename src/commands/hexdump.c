#include "hexdump.h"
#include "../stdlib/stdio.h"
#include "../stdint.h"

void hexdump(void* addr, uint32_t length) {
    uint8_t* ptr = (uint8_t*) addr;

    for (uint32_t i = 0; i < length; i += 16) {
        // Print base address of this row
        printf("%p: ", ptr + i);

        // Print hex bytes (16 per row)
        for (uint32_t j = 0; j < 16; j++) {
            if (i + j < length) {
                uint8_t byte = *(ptr + i + j);
                printf("%x ", byte);
            } else {
                printf("   "); // padding for alignment
            }
        }

        printf("\n");
    }
}