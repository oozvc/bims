; Multiboot 2 header
section .multiboot_header
header_start:
    dd 0xe85250d6                ; Magic number (Multiboot 2)
    dd 0                         ; Architecture (i386)
    dd header_end - header_start ; Header length
    
    ; Checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
    
    ; Required end tag
    dw 0    ; Type
    dw 0    ; Flags
    dd 8    ; Size
header_end: