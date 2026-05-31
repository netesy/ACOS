#include "linux_socket.h"

namespace acos::compat::linux {

u64 LinuxSocket::translate_socket_call(u32 call, u64* args) {
    (void)call; (void)args;
    return 0;
}

} // namespace acos::compat::linux
