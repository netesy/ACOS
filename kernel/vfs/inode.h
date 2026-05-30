#pragma once
#include <acos/types.h>
#include <kernel/vfs/vfs.h>

namespace acos::vfs {

class Inode {
public:
    virtual ~Inode() = default;
    virtual i32 read(u64 offset, usize size, void* buffer) = 0;
    virtual i32 write(u64 offset, usize size, const void* buffer) = 0;
    virtual u64 size() const = 0;
    virtual NodeType type() const = 0;
};

} // namespace acos::vfs
