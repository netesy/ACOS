#pragma once
#include <acos/types.h>
#include "library_manager.h"

namespace acos::loader {

class RelocationEngine {
public:
    static bool apply(LoadedLibrary* lib);
};

} // namespace acos::loader
