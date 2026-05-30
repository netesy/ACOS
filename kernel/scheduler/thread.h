#pragma once
#include <acos/types.h>

namespace acos::scheduler {

enum class ThreadState {
    Created,
    Ready,
    Running,
    Blocked,
    Suspended,
    Terminated
};

struct Process;

struct Thread {
    u64 id;
    u64 stack_top;
    u64 stack_pointer;
    ThreadState state;
    Process* parent;

    // x86_64 context would go here or be managed by stack_pointer
};

} // namespace acos::scheduler
