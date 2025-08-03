#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void* memset(void* ptr, int value, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* dest, const char* src);
char* strtok(char* str, const char* delimiters);

#endif