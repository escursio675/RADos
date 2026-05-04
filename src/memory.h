#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"

#define KERNEL_START       0xC0000000
#define KERNEL_MALLOC      0xD0000000

#define PAGE_FLAG_PRESENT  0x1
#define PAGE_FLAG_WRITE    0x2
#define PAGE_FLAG_USER     0x4
#define PAGE_FLAG_OWNER    0x200

#define REC_PAGEDIR        ((uint32_t*)  0xFFFFF000)
#define REC_PAGETABLE(i)   ((uint32_t*) (0xFFC00000 + ((i) << 12)))

extern uint32_t initial_page_dir[1024];

void     initMemory(uint32_t memHigh, uint32_t physicalAllocStart);
void     pmm_init(uint32_t memLow, uint32_t memHigh);
uint32_t pmmAllocPageFrame();
void     memMapPage(uint32_t virtualAddr, uint32_t physAddr, uint32_t flags);
uint32_t* memGetCurrentPageDir();
void     memChangePageDir(uint32_t* pd);
void     syncPageDirs();
void     invalidate(uint32_t vaddr);

#endif