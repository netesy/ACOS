#include <kernel/services/service_registry.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/hal/spinlock.h>

namespace acos::services {

static ServiceEntry g_registry[MAX_SERVICES];
static usize g_service_count = 0;
static hal::SpinLock g_registry_lock;

void init() {
    hal::ScopedLock lock(g_registry_lock);
    for (usize i = 0; i < MAX_SERVICES; i++) {
        g_registry[i].name[0] = '\0';
        g_registry[i].channel = nullptr;
        g_registry[i].owner_pid = 0;
    }
}

bool register_service(const char* name, ipc::Channel* channel, u64 pid) {
    hal::ScopedLock lock(g_registry_lock);
    if (!name || !channel || g_service_count >= MAX_SERVICES) return false;

    // Check if already exists
    for (usize i = 0; i < g_service_count; i++) {
        if (strcmp(g_registry[i].name, name) == 0) {
            return false; 
        }
    }

    ServiceEntry& entry = g_registry[g_service_count++];
    usize len = strlen(name);
    if (len >= MAX_NAME_LEN) len = MAX_NAME_LEN - 1;
    memcpy(entry.name, name, len);
    entry.name[len] = '\0';
    entry.channel = channel;
    entry.owner_pid = pid;

    return true;
}

ipc::Channel* locate_service(const char* name) {
    hal::ScopedLock lock(g_registry_lock);
    if (!name) return nullptr;

    for (usize i = 0; i < g_service_count; i++) {
        if (strcmp(g_registry[i].name, name) == 0) {
            return g_registry[i].channel;
        }
    }
    return nullptr;
}

} // namespace acos::services
