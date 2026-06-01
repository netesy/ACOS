#pragma once
#include <acos/types.h>
#include <kernel/scheduler/process.h>
#include <kernel/scheduler/thread.h>

namespace acos::scheduler {

struct RunQueue {
    Thread* head;
    Thread* tail;
    u32 count;
};

void scheduler_init();
void schedule();
void wake_thread(Thread* thread);
void block_thread(Thread* thread);
Thread* current_thread();

// SMP specific
void enqueue_thread(u32 cpu_id, Thread* thread);
Thread* dequeue_thread(u32 cpu_id);

// Statistics
usize get_thread_count();
usize get_running_thread_count();

} // namespace acos::scheduler
