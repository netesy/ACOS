#pragma once
#include <acos/types.h>
#include <kernel/scheduler/thread.h>
#include <kernel/scheduler/process.h>

namespace acos::smp {

struct GDTEntry {
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} __attribute__((packed));

struct GDTPointer {
    u16 limit;
    u64 base;
} __attribute__((packed));

struct TSSEntry {
    u32 reserved0;
    u64 rsp0;
    u64 rsp1;
    u64 rsp2;
    u64 reserved1;
    u64 ist1;
    u64 ist2;
    u64 ist3;
    u64 ist4;
    u64 ist5;
    u64 ist6;
    u64 ist7;
    u64 reserved2;
    u16 reserved3;
    u16 iopb_offset;
} __attribute__((packed));

struct CpuData {
    u64 user_rsp;       // Offset 0: Used by syscall_entry
    u64 kernel_rsp;     // Offset 8: Used by syscall_entry
    u32 apic_id;
    u32 lapic_id;
    scheduler::Thread* current_thread;
    scheduler::Process* current_process;
    bool is_bsp;
    u32 cpu_index;

    // Per-CPU GDT and TSS for secure interrupt stack-switching
    TSSEntry tss;
    GDTEntry gdt[7];
    GDTPointer gdt_ptr;
    u8 tss_stack[16384]; // Privileged stack for Ring 3 -> Ring 0 transitions
} __attribute__((aligned(64)));

class Cpu {
public:
    static void init_bsp();
    static void init_ap(u32 apic_id);
    static CpuData* current();
    static CpuData* get_by_index(u32 index) { return &g_cpus[index]; }
    static u32 count() { return g_cpu_count; }
    static u32 id() { return current()->cpu_index; }

private:
    static CpuData g_cpus[64];
    static u32 g_cpu_count;
};

} // namespace acos::smp
