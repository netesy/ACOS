#pragma once
#include <acos/types.h>

namespace acos::smp {

enum class IpiType {
    Reschedule,
    TlbShootdown,
    Panic,
    Halt
};

class Ipi {
public:
    static void send(u32 target_cpu, IpiType type);
    static void broadcast(IpiType type);
    static void handle(IpiType type);
};

} // namespace acos::smp
