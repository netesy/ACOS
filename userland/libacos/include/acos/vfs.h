#pragma once
#include <acos/types.h>
#include <acos/abi/vfs.h>

namespace acos::vfs {

using NodeType = abi::NodeType;
using DirectoryEntry = abi::DirectoryEntry;

i32 open(const char* path, u32 flags);
i32 close(i32 fd);
i32 read(i32 fd, void* buf, usize count);
i32 write(i32 fd, const void* buf, usize count);
i32 seek(i32 fd, i64 offset, u32 whence);
i32 read_dir(const char* path, DirectoryEntry* entries, usize count);
NodeType get_node_type(const char* path);
i32 pipe(i32 fds[2]);
i32 dup2(i32 old_fd, i32 new_fd);
i32 mkdir(const char* path, u32 mode = 0755);
i32 unlink(const char* path);
i32 rmdir(const char* path);

class File {
public:
    File(const char* path, u32 flags = 0);
    ~File();

    i32 read(void* buf, usize count);
    i32 write(const void* buf, usize count);
    i32 seek(i64 offset, u32 whence);
    i32 close();

    i32 fd() const { return m_fd; }
private:
    i32 m_fd;
};

class Directory {
public:
    Directory(const char* path);
    ~Directory();

    i32 read(DirectoryEntry* entries, usize count);

    const char* path() const { return m_path; }
private:
    char m_path[128];
};

} // namespace acos::vfs
