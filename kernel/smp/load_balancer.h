#pragma once
#include <acos/types.h>

namespace acos::smp {

class LoadBalancer {
public:
    static void balance();
    static u32 get_least_loaded_cpu();
};

} // namespace acos::smp
