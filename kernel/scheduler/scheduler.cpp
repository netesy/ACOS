#include <kernel/scheduler/scheduler.h>
#include <kernel/smp/cpu.h>
#include <kernel/hal/spinlock.h>

namespace acos::scheduler {

static RunQueue g_run_queues[64];
static hal::SpinLock g_queue_locks[64];

void scheduler_init() {
    for (int i = 0; i < 64; i++) {
        g_run_queues[i].head = nullptr;
        g_run_queues[i].tail = nullptr;
        g_run_queues[i].count = 0;
    }
}

void enqueue_thread(u32 cpu_id, Thread* thread) {
    hal::ScopedLock lock(g_queue_locks[cpu_id]);
    if (!g_run_queues[cpu_id].head) {
        g_run_queues[cpu_id].head = thread;
    } else {
        g_run_queues[cpu_id].tail->next = thread;
    }
    g_run_queues[cpu_id].tail = thread;
    thread->next = nullptr;
    g_run_queues[cpu_id].count++;
}

void schedule() {
    u32 cpu_id = smp::Cpu::id();
    // Context switch logic using per-CPU queues
}

Thread* current_thread() {
    return smp::Cpu::current()->current_thread;
}

void wake_thread(Thread* thread) {
    // Determine target CPU based on affinity or load
    enqueue_thread(0, thread);
}

void block_thread(Thread* thread) {
    (void)thread;
    schedule();
}

} // namespace acos::scheduler
