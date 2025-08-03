#include "memory.h"
#include "string.h"

typedef struct mem_block {
    size_t size;
    struct mem_block* next;
    int free;
} mem_block_t;

static mem_block_t* head = (mem_block_t*)MEMORY_BASE;
static uint32_t total_mem = 0;

void mm_init(uint32_t mem_upper) {
    total_mem = mem_upper * 1024;  // Convert from KB to bytes
    
    head->size = total_mem - sizeof(mem_block_t);
    head->next = NULL;
    head->free = 1;
}

void* kmalloc(size_t size) {
    // Align to 4 bytes
    size = (size + 3) & ~3;
    
    mem_block_t* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            // Split block if possible
            if (current->size > size + sizeof(mem_block_t)) {
                mem_block_t* new_block = (mem_block_t*)((uint8_t*)current + sizeof(mem_block_t) + size);
                new_block->size = current->size - size - sizeof(mem_block_t);
                new_block->next = current->next;
                new_block->free = 1;
                
                current->size = size;
                current->next = new_block;
            }
            
            current->free = 0;
            return (void*)((uint8_t*)current + sizeof(mem_block_t));
        }
        current = current->next;
    }
    return NULL;  // Out of memory
}

void kfree(void* ptr) {
    if (!ptr) return;
    
    mem_block_t* block = (mem_block_t*)((uint8_t*)ptr - sizeof(mem_block_t));
    block->free = 1;
    
    // Merge with next block if free
    if (block->next && block->next->free) {
        block->size += block->next->size + sizeof(mem_block_t);
        block->next = block->next->next;
    }
}