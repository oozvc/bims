#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define MAX_PROCESSES 16
#define STACK_SIZE 4096

typedef enum {
    READY,
    RUNNING,
    BLOCKED
} process_state_t;

typedef struct {
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    process_state_t state;
    uint32_t pid;
    char name[32];
} pcb_t;

void scheduler_init();
void create_process(void (*entry)(), const char* name);
void schedule();

#endif