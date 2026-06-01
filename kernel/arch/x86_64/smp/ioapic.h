#pragma once
#include <acos/types.h>

namespace acos::arch::x86_64 {

class IoApic {
public:
    static void init(u64 address);
    static void set_irq(u8 irq, u8 vector, u32 cpu_apic_id);
    static void mask(u8 irq);
    static void unmask(u8 irq);

private:
    static void write(u32 reg, u32 val);
    static u32 read(u32 reg);
    static u64 g_base;
};

} // namespace acos::arch::x86_64
