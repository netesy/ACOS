#pragma once
#include <acos/types.h>
#include <kernel/device/driver.h>
#include <kernel/hal/spinlock.h>

namespace acos::device {

class DriverManager {
public:
    static bool register_driver(u64 id, DriverTier tier, Driver* instance);
    static bool unregister_driver(u64 id);
    static bool set_driver_state(u64 id, DriverState state);
    static Driver* get_driver(u64 id);

private:
    static DriverDescriptor g_drivers[32];
    static usize g_driver_count;
    static hal::SpinLock g_lock;
};

} // namespace acos::device
