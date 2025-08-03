#ifndef FS_H
#define FS_H

#define MAX_FILES 32
#define MAX_FILE_NAME 32

typedef struct {
    char name[MAX_FILE_NAME];
    uint32_t size;
    uint8_t* data;
    int used;
} file_t;

void fs_init();
int file_create(const char* name);
file_t* file_open(const char* name);
int file_write(file_t* file, const void* buf, size_t size);
int file_read(file_t* file, void* buf, size_t size);

#endif