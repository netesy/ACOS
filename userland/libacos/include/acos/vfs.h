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

} // namespace acos::vfs
