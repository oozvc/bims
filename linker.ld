ENTRY(_start)

SECTIONS {
    . = 1M; /* Kernel loaded at 1MB */

    /* Multiboot header must be near the beginning */
    .multiboot_header : {
        *(.multiboot_header)
    }

    .text : ALIGN(4K) {
        *(.text)
    }

    .rodata : ALIGN(4K) {
        *(.rodata)
    }

    .data : ALIGN(4K) {
        *(.data)
    }

    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.stack)
    }

    /DISCARD/ : {
        *(.comment)
        *(.note.gnu.build-id)
    }
}
