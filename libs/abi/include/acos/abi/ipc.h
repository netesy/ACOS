#pragma once
#include <acos/types.h>

namespace acos::abi {

struct Message {
    u64 sender;
    u64 receiver;
    u32 type;
    u32 flags;
    u64 size;
    void* payload;
    u64 cap_handle;
};

} // namespace acos::abi
