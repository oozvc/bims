#include "fs.h"
#include "memory.h"
#include "string.h"

static file_t files[MAX_FILES];

void fs_init() {
    memset(files, 0, sizeof(files));
}

int file_create(const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            strcpy(files[i].name, name);
            files[i].size = 0;
            files[i].data = NULL;
            files[i].used = 1;
            return i;
        }
    }
    return -1;  // No free slots
}

file_t* file_open(const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && strcmp(files[i].name, name) == 0) {
            return &files[i];
        }
    }
    return NULL;
}

int file_write(file_t* file, const void* buf, size_t size) {
    if (!file->data || file->size < size) {
        if (file->data) kfree(file->data);
        file->data = kmalloc(size);
        if (!file->data) return -1;
    }
    
    memcpy(file->data, buf, size);
    file->size = size;
    return size;
}

int file_read(file_t* file, void* buf, size_t size) {
    if (size > file->size) size = file->size;
    memcpy(buf, file->data, size);
    return size;
}