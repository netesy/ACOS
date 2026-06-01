#pragma once
#include <acos/types.h>
namespace acos::compat::linux {
class LinuxSocket { public: static u64 translate(u32 c, u64* a); };
}
