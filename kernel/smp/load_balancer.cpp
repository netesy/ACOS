#include "load_balancer.h"
#include <kernel/scheduler/scheduler.h>
#include <kernel/smp/cpu.h>

namespace acos::smp {

void LoadBalancer::balance() {
    u32 cpu_count = Cpu::count();
    if (cpu_count <= 1) return;
    
    u32 min_load = 0xFFFFFFFF;
    u32 min_cpu = 0;
    
    for (u32 i = 0; i < cpu_count; i++) {
        u32 load = scheduler::get_run_queues()[i].count;
        if (load < min_load) {
            min_load = load;
            min_cpu = i;
        }
    }
    
    // Work stealing: move threads from overloaded CPUs to underloaded ones
    for (u32 i = 0; i < cpu_count; i++) {
        if (i == min_cpu) continue;
        
        u32 avg_load = (scheduler::get_run_queues()[i].count + min_load) / 2;
        while (scheduler::get_run_queues()[i].count > avg_load && scheduler::get_run_queues()[i].head) {
            scheduler::Thread* thread = scheduler::get_run_queues()[i].head;
            scheduler::get_run_queues()[i].head = thread->next;
            scheduler::get_run_queues()[i].count--;
            
            scheduler::enqueue_thread(min_cpu, thread);
        }
    }
}

u32 LoadBalancer::get_least_loaded_cpu() {
    u32 cpu_count = Cpu::count();
    u32 min_load = 0xFFFFFFFF;
    u32 min_cpu = 0;
    
    for (u32 i = 0; i < cpu_count; i++) {
        u32 load = scheduler::get_run_queues()[i].count;
        if (load < min_load) {
            min_load = load;
            min_cpu = i;
        }
    }
    
    return min_cpu;
}

} // namespace acos::smp
