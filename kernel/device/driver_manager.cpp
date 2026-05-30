#include <kernel/device/driver_manager.h>

namespace acos::device {

DriverDescriptor DriverManager::g_drivers[32];
usize DriverManager::g_driver_count = 0;
hal::SpinLock DriverManager::g_lock;

bool DriverManager::register_driver(u64 id, DriverTier tier, Driver* instance) {
    hal::ScopedLock lock(g_lock);
    if (g_driver_count >= 32) return false;
    g_drivers[g_driver_count++] = {id, tier, DriverState::Loaded, instance};
    return true;
}

bool DriverManager::unregister_driver(u64 id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_driver_count; i++) {
        if (g_drivers[i].id == id) {
            g_drivers[i] = g_drivers[--g_driver_count];
            return true;
        }
    }
    return false;
}

bool DriverManager::set_driver_state(u64 id, DriverState state) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_driver_count; i++) {
        if (g_drivers[i].id == id) {
            g_drivers[i].state = state;
            return true;
        }
    }
    return false;
}

Driver* DriverManager::get_driver(u64 id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_driver_count; i++) {
        if (g_drivers[i].id == id) return g_drivers[i].instance;
    }
    return nullptr;
}

} // namespace acos::device
