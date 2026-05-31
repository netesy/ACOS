#pragma once
#include <acos/types.h>

namespace acos::loader {

class SymbolResolver {
public:
    static void* resolve(const char* name, void* handle = nullptr);
};

} // namespace acos::loader
