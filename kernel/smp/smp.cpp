#include "smp.h"
#include "cpu.h"
#include <kernel/arch/x86_64/acpi/madt.h>
#include <kernel/arch/x86_64/smp/lapic.h>

namespace acos::smp {

void SmpManager::init() {
    Cpu::init_bsp();
}

void SmpManager::boot_aps() {
    u32 total_cpus = arch::x86_64::MADT::cpu_count();
    for (u32 i = 0; i < total_cpus; i++) {
        u32 apic_id = arch::x86_64::MADT::get_apic_id(i);
        if (apic_id != arch::x86_64::LocalApic::get_id()) {
            // Send INIT/SIPI to AP
            arch::x86_64::LocalApic::send_ipi(apic_id, 0); // Mock SIPI
            Cpu::init_ap(apic_id);
        }
    }
}

} // namespace acos::smp
