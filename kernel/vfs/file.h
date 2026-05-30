#pragma once
#include <acos/types.h>
#include <kernel/vfs/inode.h>

namespace acos::vfs {

class File {
public:
    File(Inode* inode);

    i32 read(void* buffer, usize size);
    i32 write(const void* buffer, usize size);
    u64 seek(u64 offset);

private:
    Inode* m_inode;
    u64 m_offset;
};

} // namespace acos::vfs
