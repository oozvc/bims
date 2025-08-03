#ifndef SYSCALL_H
#define SYSCALL_H

#define SYS_WRITE   0
#define SYS_READ    1
#define SYS_FORK    2
#define SYS_EXIT    3
#define SYS_GETPID  4

void syscall_init();
void syscall_handler();

#endif