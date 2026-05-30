#pragma once
#include <acos/types.h>
#include <kernel/scheduler/thread.h>

namespace acos::scheduler {

struct Process {
    u64 id;
    u64 address_space; // CR3 on x86_64

    // Phase 3: Capability set placeholder
    // acos::Vector<Capability*> capabilities;

    static Process* create();
};

} // namespace acos::scheduler
