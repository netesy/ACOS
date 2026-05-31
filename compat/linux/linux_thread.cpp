#include "linux_thread.h"

namespace acos::compat::linux {

void LinuxThread::setup_tls(u64 addr) {
    (void)addr;
    // Set FS/GS base for x86_64
}

} // namespace acos::compat::linux
