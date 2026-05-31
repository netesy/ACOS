#pragma once
#include <acos/types.h>

namespace acos::compat::linux {

class LinuxSignal {
public:
    static void deliver_signal(u64 pid, i32 sig);
};

} // namespace acos::compat::linux
