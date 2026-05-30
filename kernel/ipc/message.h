#pragma once
#include <acos/types.h>

namespace acos::ipc {

struct Message {
    u64 sender;
    u64 receiver;
    u32 type;
    u32 flags;
    u64 size;
    void* payload;

    // Placeholder for future capability attachment
    u64 cap_handle;
};

} // namespace acos::ipc
