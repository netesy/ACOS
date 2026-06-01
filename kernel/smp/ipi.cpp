#include "ipi.h"
#include <kernel/arch/x86_64/smp/lapic.h>

namespace acos::smp {

void Ipi::send(u32 target_cpu, IpiType type) {
    u8 vector = 0x40 + (u8)type;
    arch::x86_64::LocalApic::send_ipi(target_cpu, vector);
}

void Ipi::broadcast(IpiType type) {
    u8 vector = 0x40 + (u8)type;
    // Use LAPIC shorthand to broadcast to all CPUs except self
    volatile u32* lapic_icr = (volatile u32*)0xFEE00300;
    u32 icr_low = (vector & 0xFF) | (5 << 8) | (1 << 14) | (1 << 18);
    lapic_icr[0] = icr_low;
}

void Ipi::handle(IpiType type) {
    switch (type) {
        case IpiType::Reschedule:
            scheduler::schedule();
            break;
        case IpiType::Halt:
            __asm__("hlt");
            break;
        case IpiType::TLBFlush:
            __asm__("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax");
            break;
        default:
            break;
    }
}

} // namespace acos::smp
