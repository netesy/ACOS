#pragma once
#include <acos/types.h>

namespace acos::abi {

enum class NodeType : u32 {
    File = 1,
    Directory = 2,
    Device = 3,
};

struct DirectoryEntry {
    char name[256];
    NodeType type;
    u64 size;
};

} // namespace acos::abi
