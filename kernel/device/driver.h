#pragma once
#include <acos/types.h>
#include <kernel/device/device.h>

namespace acos::device {

enum class DriverTier {
    Tier1, // User space
    Tier2, // Protected domain
    Tier3  // Kernel
};

class Driver {
public:
    virtual ~Driver() = default;
    virtual bool initialize() = 0;
    virtual bool probe(Device* dev) = 0;
};

} // namespace acos::device
