#pragma once
#include <acos/types.h>
#include <kernel/scheduler/process.h>
#include <kernel/scheduler/thread.h>

namespace acos::scheduler {

// Forward declaration for assembly function
extern "C" void context_switch(u64* old_sp, u64 new_sp);

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

// I/O blocking: track threads waiting on device I/O.
// The idle loop polls these and wakes threads when data arrives.
void set_console_blocked(Thread* thread);
void clear_console_blocked(Thread* thread);
Thread* get_console_blocked();

// Thread creation and lookup
typedef void* (*ThreadEntry)(void*);
Thread* create_thread(ThreadEntry entry, void* arg);
Thread* find_thread(u64 thread_id);
Process* find_process(u64 process_id);

// SMP specific
void enqueue_thread(u32 cpu_id, Thread* thread);
Thread* dequeue_thread(u32 cpu_id);

// Statistics
usize get_thread_count();
usize get_running_thread_count();

// Internal helper
RunQueue* get_run_queues();

} // namespace acos::scheduler
