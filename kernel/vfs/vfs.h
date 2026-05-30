#pragma once
#include <acos/types.h>

namespace acos::vfs {

enum class NodeType {
    File,
    Directory,
    Device
};

struct Node {
    char name[256];
    NodeType type;
    u64 size;

    virtual i32 read(u64 offset, usize size, void* buffer) = 0;
    virtual i32 write(u64 offset, usize size, const void* buffer) = 0;
};

class FileSystem {
public:
    virtual Node* open(const char* path) = 0;
    virtual bool mount(const char* target) = 0;
};

void vfs_init();

} // namespace acos::vfs
