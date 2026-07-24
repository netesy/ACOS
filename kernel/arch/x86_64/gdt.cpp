#include <kernel/hal/gdt.h>
#include <kernel/smp/cpu.h>

namespace acos::hal {

void gdt_init_cpu(u32 cpu_index) {
    auto* cpu = smp::Cpu::get_by_index(cpu_index);
    if (!cpu) return;

    for (int i = 0; i < 7; i++) {
        *reinterpret_cast<u64*>(&cpu->gdt[i]) = 0;
    }

    // 0: Null
    cpu->gdt[0] = {0, 0, 0, 0, 0, 0};
    // 1: Kernel Code (0x08)
    cpu->gdt[1] = {0, 0, 0, 0x9A, 0x20, 0};
    // 2: Kernel Data (0x10)
    cpu->gdt[2] = {0, 0, 0, 0x92, 0x00, 0};
    // 3: User Data   (0x18)
    cpu->gdt[3] = {0, 0, 0, 0xF2, 0x00, 0};
    // 4: User Code   (0x20)
    cpu->gdt[4] = {0, 0, 0, 0xFA, 0x20, 0};

    // Initialize TSS
    for (usize i = 0; i < sizeof(cpu->tss); i++) {
        reinterpret_cast<u8*>(&cpu->tss)[i] = 0;
    }
    cpu->tss.rsp0 = reinterpret_cast<u64>(cpu->tss_stack) + sizeof(cpu->tss_stack);
    cpu->tss.iopb_offset = sizeof(cpu->tss);

    // 5-6: TSS (System segment, 16 bytes)
    u64 tss_base = reinterpret_cast<u64>(&cpu->tss);
    u32 tss_limit = sizeof(cpu->tss) - 1;

    cpu->gdt[5].limit_low = tss_limit & 0xFFFF;
    cpu->gdt[5].base_low = tss_base & 0xFFFF;
    cpu->gdt[5].base_middle = (tss_base >> 16) & 0xFF;
    cpu->gdt[5].access = 0x89;
    cpu->gdt[5].granularity = (tss_limit >> 16) & 0x0F;
    cpu->gdt[5].base_high = (tss_base >> 24) & 0xFF;

    *reinterpret_cast<u64*>(&cpu->gdt[6]) = tss_base >> 32;

    cpu->gdt_ptr.limit = sizeof(cpu->gdt) - 1;
    cpu->gdt_ptr.base = reinterpret_cast<u64>(&cpu->gdt);

    __asm__ volatile("lgdt %0" : : "m"(cpu->gdt_ptr));
    __asm__ volatile("ltr %%ax" : : "a"(static_cast<u16>(0x28)));
}

void tss_set_rsp0(u64 rsp0) {
    auto* cpu = smp::Cpu::current();
    if (cpu) {
        cpu->tss.rsp0 = rsp0;
    }
}

void gdt_init() {
    gdt_init_cpu(0);
}

} // namespace acos::hal
