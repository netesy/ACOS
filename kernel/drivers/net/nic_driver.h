#pragma once
#include <kernel/device/driver.h>

namespace acos::drivers::net {

class NICDriver : public device::Driver {
public:
    virtual ~NICDriver() = default;
};

} // namespace acos::drivers::net
