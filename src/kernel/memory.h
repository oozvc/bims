#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define MEMORY_BASE 0x100000  // 1MB

void mm_init(uint32_t mem_upper);
void* kmalloc(size_t size);
void kfree(void* ptr);

#endif