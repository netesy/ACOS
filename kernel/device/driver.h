#pragma once
#include <acos/types.h>

namespace acos::device {

enum class DriverTier {
    Tier1, // User space
    Tier2, // Protected domain
    Tier3  // Kernel
};

enum class DriverState {
    Unloaded,
    Loaded,
    Running,
    Failed,
    Restarting
};

class Device;

class Driver {
public:
    virtual ~Driver() = default;
    virtual bool initialize() = 0;
    virtual bool probe(Device* dev) = 0;
};

struct DriverDescriptor {
    u64 id;
    DriverTier tier;
    DriverState state;
    Driver* instance;
};

} // namespace acos::device
