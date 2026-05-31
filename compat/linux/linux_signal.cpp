#include "linux_signal.h"

namespace acos::compat::linux {

void LinuxSignal::deliver_signal(u64 pid, i32 sig) {
    (void)pid; (void)sig;
}

} // namespace acos::compat::linux
