#include "screen.h"
#include "memory.h"
#include "process.h"
#include "syscall.h"
#include "fs.h"
#include "cli.h"

// Deklarasi fungsi dari boot.asm
extern uint32_t get_memory_upper();

void kernel_main(unsigned int magic, unsigned int mb_info_addr) {
    clear_screen();
    print("CruelZiole Kernel v1.0\n");
    
    // Inisialisasi sistem
    print("Initializing Memory Manager...\n");
    mm_init(get_memory_upper());
    
    print("Initializing Filesystem...\n");
    fs_init();
    
    print("Initializing Process Scheduler...\n");
    scheduler_init();
    
    print("Initializing System Calls...\n");
    syscall_init();
    
    print("Initializing CLI...\n");
    cli_init();
    
    print("System Ready\n");
    
    // Jalankan CLI
    cli_run();
    
    // Main kernel loop
    while (1) {
        schedule();
        // Akan ada interrupt handler untuk multitasking nyata
    }
}