#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <kernel/vfs/vfs.h>
#include <acos/types.h>

extern "C" {

int errno = 0;

int open(const char *pathname, int flags, ...) {
    acos::u64 result = acos::vfs::VFS::open(pathname, flags);
    if (result == static_cast<acos::u64>(-1)) {
        errno = EACCES;
        return -1;
    }
    return static_cast<int>(result);
}

int close(int fd) {
    acos::u64 result = acos::vfs::VFS::close(fd);
    if (result != 0) {
        errno = EBADF;
        return -1;
    }
    return 0;
}

ssize_t read(int fd, void *buf, size_t count) {
    acos::i64 result = acos::vfs::VFS::read(fd, buf, count);
    if (result < 0) {
        errno = EIO;
        return -1;
    }
    return static_cast<ssize_t>(result);
}

ssize_t write(int fd, const void *buf, size_t count) {
    acos::i64 result = acos::vfs::VFS::write(fd, buf, count);
    if (result < 0) {
        errno = EIO;
        return -1;
    }
    return static_cast<ssize_t>(result);
}

off_t lseek(int fd, off_t offset, int whence) {
    (void)fd;
    (void)whence;
    return offset;
}

}
