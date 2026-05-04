#ifndef KMALLOC_H
#define KMALLOC_H

#include "stdint.h"

void  kmallocInit(uint32_t initialHeapSize);
void  changeHeapSize(int newSize);
void* kmalloc(uint32_t size);
void  kfree(void* ptr);

#endif