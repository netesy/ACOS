#pragma once
#include <acos/types.h>

namespace acos::arch::x86_64 {

class LocalApic {
public:
    static void init();
    static void eoi();
    static u32 get_id();
    static void send_ipi(u32 apic_id, u8 vector);
    static void timer_start(u32 count);
    static void timer_stop();

private:
    static void write(u32 reg, u32 val);
    static u32 read(u32 reg);
    static u64 g_base;
};

} // namespace acos::arch::x86_64
