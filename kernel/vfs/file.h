#pragma once
#include <acos/types.h>
#include <kernel/vfs/vfs.h>

namespace acos::vfs {

class File {
public:
    File(Node* node);

    i32 read(void* buffer, usize size);
    i32 write(const void* buffer, usize size);
    u64 seek(u64 offset);

private:
    Node* m_node;
    u64 m_offset;
};

} // namespace acos::vfs
