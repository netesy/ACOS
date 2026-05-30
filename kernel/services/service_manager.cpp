#include <kernel/services/service_manager.h>

namespace acos::services {

ServiceDescriptor ServiceManager::g_services[16];
usize ServiceManager::g_service_count = 0;
hal::SpinLock ServiceManager::g_lock;

bool ServiceManager::register_service(ServiceId id, u64 process_id) {
    hal::ScopedLock lock(g_lock);
    if (g_service_count >= 16) return false;
    g_services[g_service_count++] = {id, process_id, ServiceState::Stopped};
    return true;
}

bool ServiceManager::unregister_service(ServiceId id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_service_count; i++) {
        if (g_services[i].id == id) {
            g_services[i] = g_services[--g_service_count];
            return true;
        }
    }
    return false;
}

u64 ServiceManager::lookup_service(ServiceId id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_service_count; i++) {
        if (g_services[i].id == id) return g_services[i].process_id;
    }
    return 0;
}

bool ServiceManager::start_service(ServiceId id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_service_count; i++) {
        if (g_services[i].id == id) {
            g_services[i].state = ServiceState::Running;
            return true;
        }
    }
    return false;
}

bool ServiceManager::stop_service(ServiceId id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_service_count; i++) {
        if (g_services[i].id == id) {
            g_services[i].state = ServiceState::Stopped;
            return true;
        }
    }
    return false;
}

bool ServiceManager::restart_service(ServiceId id) {
    hal::ScopedLock lock(g_lock);
    for (usize i = 0; i < g_service_count; i++) {
        if (g_services[i].id == id) {
            g_services[i].state = ServiceState::Starting;
            // logic to restart process...
            g_services[i].state = ServiceState::Running;
            return true;
        }
    }
    return false;
}

} // namespace acos::services
