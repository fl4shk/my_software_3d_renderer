#include "tiny_fs.h"
#include <stdio.h>
#include <sys/fcntl.h>

#ifdef __SNOWHOUSECPU__
//union {
//        ssize_t (*read_int)(int fd, void *buf, size_t count);
//        ssize_t (*read_ptr)(void *ptr, void *buf, size_t count);
//};
//union {
//        ssize_t (*write_int)(int fd, const void *buf, size_t count);
//        ssize_t (*write_ptr)(void *ptr, const void *buf, size_t count);
//};
//union {
//        __off_t (*lseek_int)(int fd, __off_t offset, int whence);
//        __off_t (*lseek_ptr)(void *ptr, __off_t offset, int whence);
//};
//union {
//        int     (*close_int)(int fd);
//        int     (*close_ptr)(void *ptr);
//};

int open(const char* path, int mode, ...) {
    if (!(mode & O_WRONLY)) {
        return (int)tiny_fs_fopen(path, "r");
    } else {
        return (int)tiny_fs_fopen(path, "w");
    }
}

static const int FD_STDIN = 0;
static const int FD_STDOUT = 1;
static const int FD_STDERR = 2;

extern void melted_moon_write(const void* buf, size_t count);

_ssize_t read(int fd, void* buf, size_t count) {
    switch (fd) {
    case FD_STDIN: {
        for (size_t i=0; i<count; ++i) {
            ((char*)buf)[i] = '\0';
        }
        return (_ssize_t)count;
    }
    case FD_STDOUT:
    case FD_STDERR: 
        return (_ssize_t)(-1);
    default:
        return (_ssize_t)tiny_fs_fread((void*)fd, buf, (int)count);
    }
}
_ssize_t write(int fd, const void* buf, size_t count) {
    switch (fd) {
    case FD_STDIN:
        return (_ssize_t)(-1);
    case FD_STDOUT:
    case FD_STDERR:
        melted_moon_write(buf, count);
        return (_ssize_t)count;
    default: 
        return (_ssize_t)tiny_fs_fwrite((void*)fd, buf, (int)count);
    }
}

__off_t lseek(int fd, __off_t offset, int whence) {
    switch (whence) {
    case SEEK_SET:
        return (__off_t)tiny_fs_fseek(
            (void*)fd, (int)offset, TINY_FS_SEEK_SET
        );
    case SEEK_CUR:
        return (__off_t)tiny_fs_fseek(
            (void*)fd, (int)offset, TINY_FS_SEEK_CUR
        );
    case SEEK_END:
        return (__off_t)tiny_fs_fseek(
            (void*)fd, (int)offset, TINY_FS_SEEK_END
        );
    }
    return (__off_t)(-1);
}
int close(int fd) {
    tiny_fs_fclose((void*)fd);
    return 0;
}
void _exit(void) {
    for (;;) {
    }
}

#endif      // __SNOWHOUSECPU__
