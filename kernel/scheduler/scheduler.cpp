#include <acos/types.h>

namespace acos::scheduler {

enum class ThreadState {
    Ready,
    Running,
    Blocked,
    Terminated
};

struct Thread {
    u64 id;
    u64 stack_pointer;
    ThreadState state;
};

static Thread* g_current_thread = nullptr;
static Thread g_idle_thread;

void scheduler_init() {
    g_idle_thread.id = 0;
    g_idle_thread.state = ThreadState::Ready;
    g_current_thread = &g_idle_thread;
}

void schedule() {
    // Round-robin logic placeholder
    // In Phase 2, we just stick to the current thread or idle
}

} // namespace acos::scheduler
