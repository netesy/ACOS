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
    // In real implementation, uses 'swapgs' and reads from GS base.
    // For now, return BSP data.
    return &g_cpus[0];
}

} // namespace acos::smp
