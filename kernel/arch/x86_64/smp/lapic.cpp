#include "lapic.h"

namespace acos::arch::x86_64 {

u64 LocalApic::g_base = 0xFEE00000;

void LocalApic::write(u32 reg, u32 val) {
    *(volatile u32*)(g_base + reg) = val;
}

u32 LocalApic::read(u32 reg) {
    return *(volatile u32*)(g_base + reg);
}

void LocalApic::init() {
    // Spurious Interrupt Vector Register
    write(0xF0, read(0xF0) | 0x1FF);
}

void LocalApic::set_base(u64 base) {
    g_base = base;
}

u32 LocalApic::get_id() {
    return read(0x20) >> 24;
}

void LocalApic::eoi() {
    write(0xB0, 0);
}

void LocalApic::send_ipi(u32 apic_id, u8 vector) {
    write(0x310, apic_id << 24);
    write(0x300, vector | (0 << 11)); // Asserted, Destination Mode: Physical
}

} // namespace acos::arch::x86_64
