#pragma once
#include <acos/types.h>
#include <kernel/scheduler/thread.h>

namespace acos::scheduler {

void scheduler_init();
void schedule();
void block_thread(Thread* t);
void wake_thread(Thread* t);
Thread* current_thread();

// Internal helper for IPC
void remove_from_ready_queue(Thread* t);
void add_to_ready_queue(Thread* t);

} // namespace acos::scheduler
