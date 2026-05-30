#include <kernel/scheduler/scheduler.h>

namespace acos::scheduler {

static Thread* g_current_thread = nullptr;
static Thread g_idle_thread;

// Simple thread queue placeholder
static Thread* g_ready_queue[64];
static usize g_queue_count = 0;

void scheduler_init() {
    g_idle_thread.id = 0;
    g_idle_thread.state = ThreadState::Ready;
    g_current_thread = &g_idle_thread;
}

void schedule() {
    // Round-robin logic placeholder
    if (g_queue_count > 0) {
        // Switch context to next ready thread
    }
}

void block_thread(Thread* t) {
    if (!t) return;
    t->state = ThreadState::Blocked;
    // Remove from ready queue logic
    schedule();
}

void wake_thread(Thread* t) {
    if (!t) return;
    t->state = ThreadState::Ready;
    // Add to ready queue logic
    g_ready_queue[g_queue_count++] = t;
}

Thread* current_thread() {
    return g_current_thread;
}

} // namespace acos::scheduler
