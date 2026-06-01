#include "cpu.h"
#include <kernel/arch/x86_64/smp/lapic.h>

namespace acos::smp {

CpuData Cpu::g_cpus[64];
u32 Cpu::g_cpu_count = 0;

void Cpu::init_bsp() {
    g_cpus[0].apic_id = arch::x86_64::LocalApic::get_id();
    g_cpus[0].is_bsp = true;
    g_cpus[0].cpu_index = 0;
    g_cpu_count = 1;
    
    // Set GS base to point to g_cpus[0]
    u64 addr = reinterpret_cast<u64>(&g_cpus[0]);
    u32 low = static_cast<u32>(addr);
    u32 high = static_cast<u32>(addr >> 32);
    __asm__ volatile("wrmsr" : : "c"(0xC0000101), "a"(low), "d"(high));
}

void Cpu::init_ap(u32 apic_id) {
    if (g_cpu_count < 64) {
        g_cpus[g_cpu_count].apic_id = apic_id;
        g_cpus[g_cpu_count].is_bsp = false;
        g_cpus[g_cpu_count].cpu_index = g_cpu_count;
        g_cpu_count++;
    }
}

CpuData* Cpu::current() {
    u64 ptr;
    // Read GS base
    __asm__ volatile("rdmsr" : "=a"(*(u32*)&ptr), "=d"(*(((u32*)&ptr)+1)) : "c"(0xC0000101));
    return reinterpret_cast<CpuData*>(ptr);
}

} // namespace acos::smp
