#pragma once
#include <acos/types.h>
#include <kernel/scheduler/thread.h>
#include <kernel/scheduler/process.h>

namespace acos::smp {

struct CpuData {
    u32 apic_id;
    u32 lapic_id;
    u64 kernel_stack;
    scheduler::Thread* current_thread;
    scheduler::Process* current_process;
    bool is_bsp;
    u32 cpu_index;
} __attribute__((aligned(64)));

class Cpu {
public:
    static void init_bsp();
    static void init_ap(u32 apic_id);
    static CpuData* current();
    static u32 count() { return g_cpu_count; }
    static u32 id() { return current()->cpu_index; }

private:
    static CpuData g_cpus[64];
    static u32 g_cpu_count;
};

} // namespace acos::smp
