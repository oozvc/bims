#include "cli.h"
#include "screen.h"
#include "string.h"
#include "fs.h"
#include "process.h"

#define MAX_CMD_LEN 128
#define MAX_ARGS 8

static char input_buffer[MAX_CMD_LEN];
static int input_pos = 0;

void print_prompt() {
    print("\nziole@kernel$ ");
}

void execute_command(const char* cmd) {
    char cmd_copy[MAX_CMD_LEN];
    strcpy(cmd_copy, cmd);
    
    char* args[MAX_ARGS] = {0};
    int argc = 0;
    
    // Tokenize command
    char* token = strtok(cmd_copy, " ");
    while (token && argc < MAX_ARGS) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    
    if (argc == 0) return;
    
    // Built-in commands
    if (strcmp(args[0], "help") == 0) {
        print("Available commands:\n");
        print("help      - Show this help\n");
        print("clear     - Clear screen\n");
        print("ls        - List files\n");
        print("create    - Create file\n");
        print("run       - Run process\n");
        print("ps        - List processes\n");
    }
    else if (strcmp(args[0], "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(args[0], "ls") == 0) {
        print("Files:\n");
        for (int i = 0; i < MAX_FILES; i++) {
            if (files[i].used) {
                print("  ");
                print(files[i].name);
                print("\n");
            }
        }
    }
    else if (strcmp(args[0], "create") == 0 && argc > 1) {
        if (file_create(args[1]) {
            print("File created: ");
            print(args[1]);
            print("\n");
        } else {
            print("Failed to create file\n");
        }
    }
    else if (strcmp(args[0], "run") == 0 && argc > 1) {
        // Simulate running a process
        create_process(NULL, args[1]);
    }
    else if (strcmp(args[0], "ps") == 0) {
        print("Processes:\n");
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (processes[i].state != READY) {
                print("  PID: ");
                print_hex(processes[i].pid);
                print(" - ");
                print(processes[i].name);
                print(" - ");
                print(processes[i].state == RUNNING ? "RUNNING" : "BLOCKED");
                print("\n");
            }
        }
    }
    else {
        print("Unknown command: ");
        print(args[0]);
        print("\n");
    }
}

void cli_init() {
    print("Initializing CLI...\n");
    memset(input_buffer, 0, sizeof(input_buffer));
    input_pos = 0;
    print_prompt();
}

void cli_run() {
    // In real implementation, this would be called from keyboard interrupt
    // For now, we'll simulate it
    
    // Example commands:
    execute_command("help");
    execute_command("create test.txt");
    execute_command("ls");
    execute_command("run init");
    execute_command("ps");
}