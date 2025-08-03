#include "screen.h"

// Deklarasi fungsi untuk menampilkan angka hex
void print_hex(unsigned int num);

// Kernel entry point
void kernel_main(unsigned int magic, unsigned int mb_info_addr) {
    clear_screen();
    print("KernelZiole Booted Successfully!\n");
    print("Multiboot Magic: 0x");
    
    // Tampilkan magic number dalam hex
    print_hex(magic);
    
    // Tampilkan alamat info multiboot
    print("\nMultiboot Info: 0x");
    print_hex(mb_info_addr);
    
    print("\nSystem Ready\n");
    
    // Main kernel loop
    while (1) {
        // Kernel idle tasks
    }
}
