#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/hal/spinlock.h>
#include <kernel/memory/address_space.h>

namespace acos::scheduler {

static hal::SpinLock g_sched_lock;
static Thread* g_current_thread = nullptr;
static Thread g_idle_thread;

static Thread* g_ready_queue[64];
static usize g_queue_count = 0;

extern "C" void context_switch(u64* old_stack, u64 new_stack);

void scheduler_init() {
    g_idle_thread.id = 0;
    g_idle_thread.state = ThreadState::Ready;
    g_idle_thread.is_user = false;
    g_idle_thread.parent = nullptr;
    g_current_thread = &g_idle_thread;
}

void switch_to(Thread* next) {
    Thread* old = g_current_thread;
    g_current_thread = next;

    if (next->parent && next->parent->address_space) {
        u64 cr3 = next->parent->address_space->pml4_phys();
        __asm__ volatile("mov %0, %%cr3" : : "r"(cr3));
    }

    context_switch(&old->stack_pointer, next->stack_pointer);
}

void schedule() {
    hal::ScopedLock lock(g_sched_lock);

    if (g_queue_count == 0) return;

    Thread* next = g_ready_queue[0];
    for(usize i = 0; i < g_queue_count - 1; i++) {
        g_ready_queue[i] = g_ready_queue[i+1];
    }
    g_ready_queue[g_queue_count-1] = next;

    switch_to(next);
}

void remove_from_ready_queue(Thread* t) {
    for (usize i = 0; i < g_queue_count; i++) {
        if (g_ready_queue[i] == t) {
            for (usize j = i; j < g_queue_count - 1; j++) {
                g_ready_queue[j] = g_ready_queue[j+1];
            }
            g_queue_count--;
            return;
        }
    }
}

void add_to_ready_queue(Thread* t) {
    if (g_queue_count < 64) {
        g_ready_queue[g_queue_count++] = t;
    }
}

void block_thread(Thread* t) {
    hal::ScopedLock lock(g_sched_lock);
    if (!t) return;
    t->state = ThreadState::Blocked;
    remove_from_ready_queue(t);
}

void wake_thread(Thread* t) {
    hal::ScopedLock lock(g_sched_lock);
    if (!t) return;
    if (t->state == ThreadState::Blocked) {
        t->state = ThreadState::Ready;
        add_to_ready_queue(t);
    }
}

Thread* current_thread() {
    return g_current_thread;
}

} // namespace acos::scheduler
