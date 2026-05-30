#pragma once
#include <acos/types.h>

namespace acos::memory {

enum PageFlags : u64 {
    None = 0,
    Present = 1ULL << 0,
    Writable = 1ULL << 1,
    User = 1ULL << 2,
    WriteThrough = 1ULL << 3,
    NoCache = 1ULL << 4,
    Accessed = 1ULL << 5,
    Dirty = 1ULL << 6,
    HugePage = 1ULL << 7,
    Global = 1ULL << 8,
    NoExecute = 1ULL << 63
};

struct PageTable {
    u64 entries[512];
} __attribute__((aligned(4096)));

} // namespace acos::memory
