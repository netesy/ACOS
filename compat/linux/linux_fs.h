#pragma once
#include <acos/types.h>

namespace acos::compat::linux {

class LinuxFS {
public:
    static u64 translate_path(const char* linux_path, char* acos_path);
};

} // namespace acos::compat::linux
