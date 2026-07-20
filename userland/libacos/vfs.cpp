#include <acos/vfs.h>
#include <acos/syscall.h>
#include <acos/runtime.h>

namespace acos::vfs {

i32 open(const char* path, u32 flags) {
    return (i32)syscall(sys::SyscallNum::FileOpen, (u64)path, flags);
}

i32 close(i32 fd) {
    return (i32)syscall(sys::SyscallNum::FileClose, (u64)fd);
}

i32 read(i32 fd, void* buf, usize count) {
    return (i32)syscall(sys::SyscallNum::FileRead, (u64)fd, (u64)buf, count);
}

i32 write(i32 fd, const void* buf, usize count) {
    return (i32)syscall(sys::SyscallNum::FileWrite, (u64)fd, (u64)buf, count);
}

i32 seek(i32 fd, i64 offset, u32 whence) {
    return (i32)syscall(sys::SyscallNum::FileSeek, (u64)fd, (u64)offset, (u64)whence);
}

i32 read_dir(const char* path, DirectoryEntry* entries, usize count) {
    return (i32)syscall(sys::SyscallNum::FileReadDir, (u64)path, (u64)entries, count);
}

NodeType get_node_type(const char* path) {
    return (NodeType)syscall(sys::SyscallNum::ResourceQuery, (u64)path);
}

i32 pipe(i32 fds[2]) {
    return (i32)syscall(sys::SyscallNum::PipeCreate, (u64)fds);
}

i32 dup2(i32 old_fd, i32 new_fd) {
    return (i32)syscall(sys::SyscallNum::FileDup, (u64)old_fd, (u64)new_fd);
}

// File wrapper implementation
File::File(const char* path, u32 flags) {
    m_fd = open(path, flags);
}

File::~File() {
    close();
}

i32 File::read(void* buf, usize count) {
    if (m_fd < 0) return -1;
    return vfs::read(m_fd, buf, count);
}

i32 File::write(const void* buf, usize count) {
    if (m_fd < 0) return -1;
    return vfs::write(m_fd, buf, count);
}

i32 File::seek(i64 offset, u32 whence) {
    if (m_fd < 0) return -1;
    return vfs::seek(m_fd, offset, whence);
}

i32 File::close() {
    if (m_fd >= 0) {
        i32 res = vfs::close(m_fd);
        m_fd = -1;
        return res;
    }
    return 0;
}

// Directory wrapper implementation
Directory::Directory(const char* path) {
    usize len = 0;
    while (path[len] && len < 127) {
        m_path[len] = path[len];
        len++;
    }
    m_path[len] = '\0';
}

Directory::~Directory() {}

i32 Directory::read(DirectoryEntry* entries, usize count) {
    return read_dir(m_path, entries, count);
}

} // namespace acos::vfs
