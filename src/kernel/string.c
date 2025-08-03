#include "string.h"

void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = ptr;
    while (num--) *p++ = (unsigned char)value;
    return ptr;
}

void* memcpy(void* dest, const void* src, size_t num) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    while (num--) *d++ = *s++;
    return dest;
}

int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char* strcpy(char* dest, const char* src) {
    char* save = dest;
    while ((*dest++ = *src++));
    return save;
}

char* strtok(char* str, const char* delimiters) {
    static char* next_token = NULL;
    if (str) next_token = str;
    if (!next_token || !*next_token) return NULL;
    
    // Skip delimiters
    char* token_start = next_token;
    while (*next_token) {
        const char* delim = delimiters;
        while (*delim) {
            if (*next_token == *delim) {
                *next_token = '\0';
                next_token++;
                return token_start;
            }
            delim++;
        }
        next_token++;
    }
    
    return token_start;
}