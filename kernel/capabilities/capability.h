#pragma once
#include <acos/types.h>

namespace acos::capabilities {

enum class CapabilityType {
    Memory,
    Device,
    Process,
    Socket,
    Channel,
    Graphics,
    Audio
};

/**
 * Graphics Capability Rights
 */
namespace GraphicsRights {
    static constexpr u64 CREATE_WINDOW   = 1 << 0;
    static constexpr u64 CREATE_SURFACE  = 1 << 1;
    static constexpr u64 DISPLAY_CONTROL = 1 << 2;
    static constexpr u64 INPUT_CAPTURE   = 1 << 3;
    static constexpr u64 SESSION_ADMIN   = 1 << 4;
}

/**
 * Audio Capability Rights
 */
namespace AudioRights {
    static constexpr u64 PLAYBACK       = 1 << 0;
    static constexpr u64 RECORD         = 1 << 1;
    static constexpr u64 ADMIN          = 1 << 2;
    static constexpr u64 DEVICE_CONTROL = 1 << 3;
    static constexpr u64 STREAM_CREATE  = 1 << 4;
}

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
