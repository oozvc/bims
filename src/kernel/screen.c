#include "screen.h"

#define VIDEO_MEMORY 0xB8000
#define WIDTH 80
#define HEIGHT 25

static int cursor_x = 0;
static int cursor_y = 0;

void clear_screen() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            video[2 * (y * WIDTH + x)] = ' ';
            video[2 * (y * WIDTH + x) + 1] = 0x0F;
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void print(const char* str) {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            video[2 * (cursor_y * WIDTH + cursor_x)] = *str;
            video[2 * (cursor_y * WIDTH + cursor_x) + 1] = 0x0F;
            cursor_x++;
        }
        
        if (cursor_x >= WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
        
        // Scroll screen if needed
        if (cursor_y >= HEIGHT) {
            for (int y = 1; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    video[2 * ((y-1) * WIDTH + x)] = video[2 * (y * WIDTH + x)];
                    video[2 * ((y-1) * WIDTH + x) + 1] = video[2 * (y * WIDTH + x) + 1];
                }
            }
            
            // Clear last line
            for (int x = 0; x < WIDTH; x++) {
                video[2 * ((HEIGHT-1) * WIDTH + x)] = ' ';
                video[2 * ((HEIGHT-1) * WIDTH + x) + 1] = 0x0F;
            }
            
            cursor_y = HEIGHT - 1;
        }
        
        str++;
    }
}