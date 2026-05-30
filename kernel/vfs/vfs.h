#pragma once
#include <acos/types.h>

namespace acos::vfs {

enum class NodeType {
    File,
    Directory,
    Device
};

class File;
class FileSystem;
struct Inode;
class Dentry;

class VFS {
public:
    static i32 open(const char* path, u64 flags);
    static i32 close(u64 fd);
    static i32 read(u64 fd, void* buffer, usize size);
    static i32 write(u64 fd, const void* buffer, usize size);
    static bool mount(const char* path, FileSystem* fs);
};

} // namespace acos::vfs
