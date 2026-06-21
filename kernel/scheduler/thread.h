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

struct ThreadContext {
    u64 r15, r14, r13, r12, rbx, rbp;
    u64 rip, cs, rflags, rsp, ss;
};

struct Thread {
    u64 id;
    u64 stack_top;
    u64 stack_pointer;
    ThreadState state;
    Process* parent;
    bool is_user;
    void* return_value;
    Thread* next;  // For run queue linking
    u64 entry_point;
    void* arg;
};

} // namespace acos::scheduler
