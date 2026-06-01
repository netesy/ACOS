#pragma once
#include <acos/types.h>

namespace acos::smp {

class SmpManager {
public:
    static void init();
    static void boot_aps();
};

} // namespace acos::smp
