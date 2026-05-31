#pragma once
#include <acos/types.h>

namespace acos::compat::linux {

class LinuxSocket {
public:
    static u64 translate_socket_call(u32 call, u64* args);
};

} // namespace acos::compat::linux
