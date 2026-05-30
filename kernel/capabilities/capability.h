#pragma once
#include <acos/types.h>

namespace acos::capabilities {

enum class CapabilityType {
    Memory,
    Device,
    Process,
    Socket,
    Channel
};

struct Capability {
    u64 id;
    CapabilityType type;
    u64 rights;
    u64 owner_process_id;
};

// Core capability management functions
bool transfer(u64 cap_id, u64 source_process_id, u64 target_process_id);
bool revoke(u64 cap_id, u64 process_id);

} // namespace acos::capabilities
