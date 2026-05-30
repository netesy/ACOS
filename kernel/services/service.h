#pragma once
#include <acos/types.h>

namespace acos::services {

enum class ServiceId : u64 {
    Filesystem = 1,
    Network = 2,
    Graphics = 3,
    Audio = 4,
    Identity = 5
};

enum class ServiceState {
    Stopped,
    Starting,
    Running,
    Failed
};

struct ServiceDescriptor {
    ServiceId id;
    u64 process_id;
    ServiceState state;
};

} // namespace acos::services
