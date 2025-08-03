; Bootloader entry point
global _start
extern kernel_main

section .text
bits 32
_start:
    ; Setup stack
    mov esp, stack_top
    
    ; Pass multiboot info to kernel
    push ebx ; Multiboot info structure
    push eax ; Multiboot magic number
    
    ; Call kernel main
    call kernel_main
    
    ; Halt if kernel returns
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384 ; 16KB stack
stack_top: