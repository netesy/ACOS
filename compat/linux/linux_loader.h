#pragma once
#include <acos/types.h>
namespace acos::compat::linux {
class LinuxLoader {
public:
    static bool load_linux_binary(const char* path);
};
}
