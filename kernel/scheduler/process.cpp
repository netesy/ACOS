#include <kernel/scheduler/process.h>
#include <acos/types.h>

namespace acos::scheduler {

static u64 g_next_process_id = 1;

Process* Process::create() {
    // In a real system, we'd use an allocator here
    // For Phase 3 foundation, we use a static pool or just a placeholder
    static Process g_process_pool[64];
    static u64 g_pool_index = 0;

    if (g_pool_index >= 64) return nullptr;

    Process* p = &g_process_pool[g_pool_index++];
    p->id = g_next_process_id++;
    p->address_space = 0; // Kernel space initially

    return p;
}

} // namespace acos::scheduler
