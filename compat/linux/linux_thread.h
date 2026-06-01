#pragma once
#include <acos/types.h>
namespace acos::compat::linux {
class LinuxThread { public: static void setup_tls(u64 addr); };
}
