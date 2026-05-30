#pragma once
#include <acos/types.h>

namespace acos::vfs {

class Path {
public:
    static void normalize(char* path);
    static bool is_absolute(const char* path);

    // Future: helper to split path into components
};

} // namespace acos::vfs
