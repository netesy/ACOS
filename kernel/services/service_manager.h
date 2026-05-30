#pragma once
#include <acos/types.h>
#include <kernel/services/service.h>
#include <kernel/hal/spinlock.h>

namespace acos::services {

class ServiceManager {
public:
    static bool register_service(ServiceId id, u64 process_id);
    static bool unregister_service(ServiceId id);
    static u64 lookup_service(ServiceId id);
    static bool start_service(ServiceId id);
    static bool stop_service(ServiceId id);
    static bool restart_service(ServiceId id);

private:
    static ServiceDescriptor g_services[16];
    static usize g_service_count;
    static hal::SpinLock g_lock;
};

} // namespace acos::services
