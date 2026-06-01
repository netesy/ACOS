#include "linux_socket.h"
#include <userland/posix/include/sys/socket.h>

namespace acos::compat::linux {

namespace {

constexpr u64 LinuxAfInet = 2;
constexpr u64 LinuxAfInet6 = 10;
constexpr u64 LinuxSockStream = 1;
constexpr u64 LinuxSockDgram = 2;

} // namespace

u64 LinuxSocket::translate(u32 c, u64* args) {
    (void)c;
    if (!args) return static_cast<u64>(-1);

    if (args[0] == LinuxAfInet) {
        args[0] = AF_INET;
    } else if (args[0] == LinuxAfInet6) {
        args[0] = AF_INET6;
    } else {
        return static_cast<u64>(-1);
    }

    if (args[1] == LinuxSockStream) {
        args[1] = SOCK_STREAM;
    } else if (args[1] == LinuxSockDgram) {
        args[1] = SOCK_DGRAM;
    } else {
        return static_cast<u64>(-1);
    }

    return 0;
}

} // namespace acos::compat::linux
