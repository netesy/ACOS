#pragma once
#include <acos/types.h>
namespace acos::compat::linux {
class LinuxFS { public: static u64 translate(const char* lp, char* ap); };
}
