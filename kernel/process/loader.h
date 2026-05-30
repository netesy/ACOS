#pragma once
#include <acos/types.h>
#include <kernel/scheduler/process.h>

namespace acos::process {

struct UserImage {
    u64 entry_point;
    u64 stack_top;
};

scheduler::Process* create_user_process(const char* name, u64 entry_point);

} // namespace acos::process
