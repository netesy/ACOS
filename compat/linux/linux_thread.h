#pragma once
#include <acos/types.h>
#include <kernel/scheduler/scheduler.h>

namespace acos::compat::linux {

class LinuxThread {
public:
    static void setup_tls(u64 addr);
};

} // namespace acos::compat::linux
