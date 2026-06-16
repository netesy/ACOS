#include <acos/process.h>
#include <acos/runtime.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <acos/types.h>
#include <acos/runtime.h>
#include <libs/runtime/include/acos/runtime.h>

extern "C" {

int open(const char *pathname, int flags, ...) {
    acos::i32 result = acos::vfs::VFS::open(pathname, flags);
    if (result < 0) {
        errno = EACCES;
        return -1;
    }
    return result;
}

int close(int fd) {
    acos::i32 result = acos::vfs::VFS::close(fd);
    if (result != 0) {
        errno = EBADF;
        return -1;
    }
    return 0;
}

ssize_t read(int fd, void *buf, size_t count) {
    acos::i32 result = acos::vfs::VFS::read(fd, buf, count);
    if (result < 0) {
        errno = EIO;
        return -1;
    }
    return static_cast<ssize_t>(result);
}

ssize_t write(int fd, const void *buf, size_t count) {
    acos::i32 result = acos::vfs::VFS::write(fd, buf, count);
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

// Directory operations
DIR *opendir(const char *name) {
    if (!name) return nullptr;

    // In our simplified VFS, we don't have separate DIR handles,
    // but we can check if it exists and is a directory.
    if (acos::vfs::VFS::get_node_type(name) != acos::vfs::NodeType::Directory) {
        errno = ENOTDIR;
        return nullptr;
    }

    DIR* dir = (DIR*)acos::memory::kmalloc(sizeof(DIR));
    if (!dir) return nullptr;

    // We'll store the path in a custom way if needed, but for now just mock it
    // because VFS::read_dir takes a path.
    // Wait, POSIX readdir needs to maintain state.
    // For now, let's just make it work for the FileManager using direct VFS.
    dir->fd = 0; // Placeholder
    return dir;
}

struct dirent *readdir(DIR *dirp) {
    (void)dirp;
    return nullptr; // Not fully implemented yet
}

int closedir(DIR *dirp) {
    if (dirp) acos::memory::kfree(dirp);
    return 0;
}

}
