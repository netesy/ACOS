#pragma once
#include <acos/types.h>

namespace acos::vfs {

enum class NodeType {
    File,
    Directory,
    Device
};

class Node {
public:
    virtual ~Node() = default;
    virtual i32 read(u64 offset, usize size, void* buffer) = 0;
    virtual i32 write(u64 offset, usize size, const void* buffer) = 0;
    virtual u64 size() const = 0;
    virtual NodeType type() const = 0;
};

class FileSystem {
public:
    virtual ~FileSystem() = default;
    virtual Node* open(const char* path) = 0;
    virtual bool mount(const char* target) = 0;
};

class File;
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
