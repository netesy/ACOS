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
    hal::ScopedLock lock(g_queue_locks[cpu_id]);
    
    CpuData* cpu = smp::Cpu::current();
    if (!cpu) return;
    
    // Get next thread from run queue
    Thread* next = g_run_queues[cpu_id].head;
    if (!next) {
        // No threads to run, idle
        return;
    }
    
    // Remove from queue
    g_run_queues[cpu_id].head = next->next;
    if (!g_run_queues[cpu_id].head) {
        g_run_queues[cpu_id].tail = nullptr;
    }
    g_run_queues[cpu_id].count--;
    
    // Get current thread
    Thread* current = cpu->current_thread;
    
    // If current thread is still runnable, re-enqueue it
    if (current && current->state == ThreadState::Running) {
        current->state = ThreadState::Ready;
        enqueue_thread(cpu_id, current);
    }
    
    // Switch to next thread
    if (next != current) {
        next->state = ThreadState::Running;
        cpu->current_thread = next;
        
        // Perform context switch
        if (current) {
            context_switch(&current->stack_pointer, next->stack_pointer);
        } else {
            // First thread on this CPU
            __asm__ volatile("mov %0, %%rsp" : : "r"(next->stack_pointer));
        }
    }
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


usize get_thread_count() {
    // Count total threads across all CPUs
    usize total = 0;
    for (int i = 0; i < 64; i++) {
        total += g_run_queues[i].count;
    }
    return total;
}

usize get_running_thread_count() {
    // Count running threads (simplified: return threads in run queues)
    // In a full implementation, would track actual running vs ready threads
    return get_thread_count();
}
