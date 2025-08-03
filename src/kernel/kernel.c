#include "screen.h"

// Kernel entry point
void kernel_main(unsigned int magic, unsigned int mb_info_addr) {
    clear_screen();
    print("KernelZiole Booted Successfully!\n");
    print("Multiboot Magic: 0x");
    
    // Print magic number in hex
    char hex[9];
    for (int i = 0; i < 8; i++) {
        int digit = (magic >> (28 - i*4)) & 0xF;
        hex[i] = digit < 10 ? '0' + digit : 'A' + digit - 10;
    }
    hex[8] = '\0';
    print(hex);
    
    print("\nSystem Ready\n");
    
    // Main kernel loop
    while (1) {
        // Kernel idle tasks
    }
}