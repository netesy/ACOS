#pragma once
#include <acos/types.h>

namespace acos::loader {

class RuntimeLoader {
public:
    static bool load_library(const char* path);
    static void* get_symbol(const char* name);
    static void initialize();
};

} // namespace acos::loader
