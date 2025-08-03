#include "syscall.h"
#include "process.h"
#include "screen.h"
#include "fs.h"

void* syscalls[5] = {0};

void syscall_init() {
    syscalls[SYS_WRITE] = sys_write;
    syscalls[SYS_READ] = sys_read;
    syscalls[SYS_FORK] = sys_fork;
    syscalls[SYS_EXIT] = sys_exit;
    syscalls[SYS_GETPID] = sys_getpid;
}

void syscall_handler() {
    asm volatile(
        "pusha\n"
        "call syscall_dispatcher\n"
        "popa\n"
        "iret\n"
    );
}

void syscall_dispatcher() {
    uint32_t eax, ebx, ecx, edx;
    asm volatile(
        "mov %%eax, %0\n"
        "mov %%ebx, %1\n"
        "mov %%ecx, %2\n"
        "mov %%edx, %3"
        : "=r"(eax), "=r"(ebx), "=r"(ecx), "=r"(edx)
    );
    
    if (eax < 5 && syscalls[eax]) {
        void (*func)(uint32_t, uint32_t, uint32_t) = syscalls[eax];
        func(ebx, ecx, edx);
    }
}

// Implementations
void sys_write(uint32_t fd, uint32_t buf, uint32_t len) {
    char* str = (char*)buf;
    for (uint32_t i = 0; i < len; i++) {
        put_char(str[i], cursor_x, cursor_y);
        // Update cursor position...
    }
}

void sys_read(uint32_t fd, uint32_t buf, uint32_t len) {
    // Implement later
}

void sys_fork(uint32_t unused1, uint32_t unused2, uint32_t unused3) {
    create_process(current_process->eip, "child");
}

void sys_exit(uint32_t status, uint32_t unused1, uint32_t unused2) {
    if (current_process) {
        current_process->state = READY;
        print("Process exited: ");
        print(current_process->name);
        print("\n");
        schedule();
    }
}

void sys_getpid(uint32_t unused1, uint32_t unused2, uint32_t unused3) {
    if (current_process) {
        asm volatile("mov %0, %%eax" :: "r"(current_process->pid));
    }
}