#pragma once
#include <acos/types.h>
namespace acos::compat::linux {
class LinuxSignal { public: static void deliver(u64 pid, i32 sig); };
}
