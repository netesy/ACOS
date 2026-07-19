#include <acos/vfs.h>
#include <acos/syscall.h>

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
    return (NodeType)syscall(sys::SyscallNum::ResourceQuery, (u64)path); // Reuse ResourceQuery for NodeType
}

i32 pipe(i32 fds[2]) {
    return (i32)syscall(sys::SyscallNum::PipeCreate, (u64)fds);
}

i32 dup2(i32 old_fd, i32 new_fd) {
    return (i32)syscall(sys::SyscallNum::FileDup, (u64)old_fd, (u64)new_fd);
}

} // namespace acos::vfs
