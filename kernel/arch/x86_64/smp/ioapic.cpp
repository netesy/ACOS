#include "ioapic.h"

namespace acos::arch::x86_64 {

u64 IoApic::g_base = 0xFEC00000;

void IoApic::write(u32 reg, u32 val) {
    *(volatile u32*)(g_base + 0x00) = reg;
    *(volatile u32*)(g_base + 0x10) = val;
}

u32 IoApic::read(u32 reg) {
    *(volatile u32*)(g_base + 0x00) = reg;
    return *(volatile u32*)(g_base + 0x10);
}

void IoApic::init(u64 address) {
    g_base = address;
}

void IoApic::set_irq(u8 irq, u8 vector, u32 cpu_apic_id) {
    u32 low = vector & 0xFF;
    u32 high = cpu_apic_id << 24;

    write(0x10 + irq * 2, low);
    write(0x11 + irq * 2, high);
}

} // namespace acos::arch::x86_64
