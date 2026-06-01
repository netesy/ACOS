#include "load_balancer.h"
#include <kernel/scheduler/scheduler.h>

namespace acos::smp {

void LoadBalancer::balance() {
    // Basic work stealing logic
}

u32 LoadBalancer::get_least_loaded_cpu() {
    return 0; // Return index of CPU with shortest run queue
}

} // namespace acos::smp
