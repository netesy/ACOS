#include "ipi.h"
#include <kernel/arch/x86_64/smp/lapic.h>

namespace acos::smp {

void Ipi::send(u32 target_cpu, IpiType type) {
    u8 vector = 0x40 + (u8)type;
    arch::x86_64::LocalApic::send_ipi(target_cpu, vector);
}

void Ipi::broadcast(IpiType type) {
    (void)type;
    // Implementation for broadast using LAPIC shorthand
}

void Ipi::handle(IpiType type) {
    (void)type;
    // Dispatch IPI handler
}

} // namespace acos::smp
