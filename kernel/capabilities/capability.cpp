#include <kernel/capabilities/capability.h>

namespace acos::capabilities {

static Capability g_cap_pool[1024];
static u64 g_pool_index = 0;

bool transfer(u64 cap_id, u64 source_process_id, u64 target_process_id) {
    for (u64 i = 0; i < g_pool_index; i++) {
        if (g_cap_pool[i].id == cap_id && g_cap_pool[i].owner_process_id == source_process_id) {
            g_cap_pool[i].owner_process_id = target_process_id;
            return true;
        }
    }
    return false;
}

bool revoke(u64 cap_id, u64 process_id) {
    for (u64 i = 0; i < g_pool_index; i++) {
        if (g_cap_pool[i].id == cap_id && g_cap_pool[i].owner_process_id == process_id) {
            // Very simple revocation: just zero it out or mark as invalid
            g_cap_pool[i].id = 0;
            return true;
        }
    }
    return false;
}

} // namespace acos::capabilities
