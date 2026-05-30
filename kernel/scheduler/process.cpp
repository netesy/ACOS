#include <kernel/scheduler/process.h>
#include <acos/types.h>

namespace acos::scheduler {

static u64 g_next_process_id = 1;

Process* Process::create() {
    static Process g_process_pool[64];
    static u64 g_pool_index = 0;

    if (g_pool_index >= 64) return nullptr;

    Process* p = &g_process_pool[g_pool_index++];
    p->id = g_next_process_id++;
    p->address_space = 0;

    for (usize i = 0; i < MAX_HANDLES; i++) {
        p->channels[i] = nullptr;
        p->regions[i] = nullptr;
        p->notifications[i] = nullptr;
    }

    return p;
}

u64 Process::register_channel(acos::ipc::Channel* chan) {
    for (usize i = 1; i < MAX_HANDLES; i++) {
        if (!channels[i]) {
            channels[i] = chan;
            return i;
        }
    }
    return 0;
}

acos::ipc::Channel* Process::get_channel(u64 handle) {
    if (handle >= MAX_HANDLES) return nullptr;
    return channels[handle];
}

u64 Process::register_region(acos::ipc::SharedRegion* reg) {
    for (usize i = 1; i < MAX_HANDLES; i++) {
        if (!regions[i]) {
            regions[i] = reg;
            return i;
        }
    }
    return 0;
}

acos::ipc::SharedRegion* Process::get_region(u64 handle) {
    if (handle >= MAX_HANDLES) return nullptr;
    return regions[handle];
}

u64 Process::register_notification(acos::ipc::Notification* note) {
    for (usize i = 1; i < MAX_HANDLES; i++) {
        if (!notifications[i]) {
            notifications[i] = note;
            return i;
        }
    }
    return 0;
}

acos::ipc::Notification* Process::get_notification(u64 handle) {
    if (handle >= MAX_HANDLES) return nullptr;
    return notifications[handle];
}

} // namespace acos::scheduler
