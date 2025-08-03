; Bootloader dengan header Multiboot 1
section .multiboot_header
align 4
header_start:
    dd 0x1BADB002              ; Magic number (Multiboot 1)
    dd 0x00000003              ; Flags (align modules + provide memory map)
    dd -(0x1BADB002 + 0x00000003) ; Checksum

section .text
global _start
extern kernel_main

; Fungsi untuk mendapatkan memori atas
global get_memory_upper
get_memory_upper:
    mov eax, [mem_upper]
    ret

_start:
    ; Setup stack
    mov esp, stack_top
    
    ; Simpan informasi memori atas
    mov eax, [ebx + 8]  ; Upper memory in KB
    mov [mem_upper], eax
    
    ; Pass multiboot info to kernel
    push ebx ; Multiboot info structure pointer
    push eax ; Multiboot magic number
    
    ; Call kernel main
    call kernel_main
    
    ; Halt if kernel returns
    cli
.hang:
    hlt
    jmp .hang

section .data
mem_upper: dd 0

section .bss
align 16
stack_bottom:
    resb 16384 ; 16KB stack
stack_top: