#include "stdint.h"
#include "util.h"
#include "memory.h"
#include "kmalloc.h"

static uint32_t heapStart;
static uint32_t heapSize;
static uint32_t threshold;
static uint8_t  kmallocInitalized = 0;

void kmallocInit(uint32_t initialHeapSize) {
    heapStart          = KERNEL_MALLOC;
    heapSize           = 0;
    threshold          = 0;
    kmallocInitalized  = 1;
    changeHeapSize(initialHeapSize);
    *((uint32_t*)heapStart) = 0;
}

void changeHeapSize(int newSize) {
    int oldPageTop = CEIL_DIV(heapSize, 0x1000);
    int newPageTop = CEIL_DIV(newSize,  0x1000);

    if (newPageTop > oldPageTop) {
        int diff = newPageTop - oldPageTop;
        for (int i = 0; i < diff; i++) {
            uint32_t phys = pmmAllocPageFrame();
            memMapPage(KERNEL_MALLOC + oldPageTop * 0x1000 + i * 0x1000,
                       phys, PAGE_FLAG_WRITE);
        }
    }
    heapSize = newSize;
}

void* kmalloc(uint32_t size) {
    if (!kmallocInitalized) return 0;

    // Align to 4 bytes
    if (size % 4 != 0) {
        size += 4 - (size % 4);
    }

    uint32_t addr = heapStart + threshold;
    threshold += size;

    if (threshold > heapSize) {
        changeHeapSize(threshold + 0x1000);
    }

    return (void*) addr;
}

void kfree(void* ptr) {
    // Bump allocator — free is no-op for now
    (void)ptr;
}