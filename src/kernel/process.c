#include "process.h"
#include "memory.h"
#include "screen.h"

static pcb_t processes[MAX_PROCESSES];
static pcb_t* current_process = NULL;
static uint32_t next_pid = 1;

void scheduler_init() {
    memset(processes, 0, sizeof(processes));
}

void create_process(void (*entry)(), const char* name) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == READY) continue;
        
        // Allocate stack
        uint8_t* stack = kmalloc(STACK_SIZE);
        if (!stack) return;
        
        // Set up PCB
        processes[i].esp = (uint32_t)(stack + STACK_SIZE - sizeof(uint32_t));
        processes[i].ebp = processes[i].esp;
        processes[i].eip = (uint32_t)entry;
        processes[i].state = READY;
        processes[i].pid = next_pid++;
        strcpy(processes[i].name, name);
        
        // Set up stack frame
        uint32_t* stack_top = (uint32_t*)processes[i].esp;
        *--stack_top = 0x202;  // EFLAGS
        *--stack_top = 0x8;    // CS
        *--stack_top = (uint32_t)entry;  // EIP
        processes[i].esp = (uint32_t)stack_top;
        
        print("Created process: ");
        print(name);
        print("\n");
        return;
    }
    print("Max processes reached\n");
}

void schedule() {
    static int last = 0;
    
    if (!current_process || current_process->state != RUNNING) {
        current_process = NULL;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (processes[i].state == READY) {
                current_process = &processes[i];
                current_process->state = RUNNING;
                break;
            }
        }
    }
    
    if (current_process) {
        // Switch to next process
        int next = (last + 1) % MAX_PROCESSES;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (processes[next].state == READY) {
                current_process->state = READY;
                processes[next].state = RUNNING;
                current_process = &processes[next];
                last = next;
                break;
            }
            next = (next + 1) % MAX_PROCESSES;
        }
    }
    
    // If no processes, idle
}