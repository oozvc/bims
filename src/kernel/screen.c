#include "screen.h"

#define VIDEO_MEMORY 0xB8000
#define WIDTH 80
#define HEIGHT 25

static int cursor_x = 0;
static int cursor_y = 0;

// Fungsi untuk menampilkan karakter di posisi tertentu
static void put_char(char c, int x, int y) {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    video[2 * (y * WIDTH + x)] = c;
    video[2 * (y * WIDTH + x) + 1] = 0x0F;
}

void clear_screen() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            put_char(' ', x, y);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void print(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            put_char(*str, cursor_x, cursor_y);
            cursor_x++;
        }
        
        if (cursor_x >= WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
        
        // Scroll screen jika perlu
        if (cursor_y >= HEIGHT) {
            volatile char* video = (volatile char*)VIDEO_MEMORY;
            
            // Geser semua baris ke atas
            for (int y = 1; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    video[2 * ((y-1) * WIDTH + x)] = video[2 * (y * WIDTH + x)];
                    video[2 * ((y-1) * WIDTH + x) + 1] = video[2 * (y * WIDTH + x) + 1];
                }
            }
            
            // Bersihkan baris terakhir
            for (int x = 0; x < WIDTH; x++) {
                put_char(' ', x, HEIGHT - 1);
            }
            
            cursor_y = HEIGHT - 1;
        }
        
        str++;
    }
}

// Fungsi baru untuk menampilkan angka hex
void print_hex(unsigned int num) {
    char hex_chars[] = "0123456789ABCDEF";
    
    // Tampilkan prefix "0x"
    print("0x");
    
    // Tampilkan setiap digit hex (8 digit untuk 32-bit)
    for (int i = 7; i >= 0; i--) {
        int digit = (num >> (i * 4)) & 0xF;
        put_char(hex_chars[digit], cursor_x, cursor_y);
        cursor_x++;
        
        if (cursor_x >= WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }
}
