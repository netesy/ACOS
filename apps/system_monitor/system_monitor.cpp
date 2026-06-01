#include "system_monitor.h"
#include <kernel/scheduler/scheduler.h>
#include <kernel/memory/pmm.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::apps {

SystemMonitor::SystemMonitor() : gui::WindowWidget("System Monitor", 300, 100, 300, 200),
                                 m_cpu_label("CPU: 0%"), m_mem_label("MEM: 0%") {
    add_child(&m_cpu_label);
    add_child(&m_mem_label);

    m_cpu_label.set_position(320, 140);
    m_mem_label.set_position(320, 170);
}

void SystemMonitor::refresh() {
    // Update CPU usage statistics
    // In a full implementation, this would:
    // 1. Query scheduler for CPU load
    // 2. Calculate per-CPU utilization
    // 3. Get total system load
    
    // Get total threads and running threads
    usize total_threads = acos::scheduler::get_thread_count();
    usize running_threads = acos::scheduler::get_running_thread_count();
    
    // Calculate CPU percentage (simplified)
    u32 cpu_percent = (running_threads * 100) / (total_threads > 0 ? total_threads : 1);
    if (cpu_percent > 100) cpu_percent = 100;
    
    // Update memory usage statistics
    // In a full implementation, this would:
    // 1. Query PMM for allocated pages
    // 2. Calculate total system memory
    // 3. Calculate percentage used
    
    // Get memory statistics
    u64 total_memory = acos::memory::pmm_get_total_memory();
    u64 used_memory = acos::memory::pmm_get_used_memory();
    
    // Calculate memory percentage
    u32 mem_percent = 0;
    if (total_memory > 0) {
        mem_percent = (used_memory * 100) / total_memory;
    }
    if (mem_percent > 100) mem_percent = 100;
    
    // Update labels with current values
    // Use simple string formatting without sprintf
    char cpu_buf[32];
    char mem_buf[32];
    
    // Format CPU label: "CPU: XX%"
    cpu_buf[0] = 'C';
    cpu_buf[1] = 'P';
    cpu_buf[2] = 'U';
    cpu_buf[3] = ':';
    cpu_buf[4] = ' ';
    
    // Convert percentage to string
    usize pos = 5;
    if (cpu_percent >= 100) {
        cpu_buf[pos++] = '1';
        cpu_buf[pos++] = '0';
        cpu_buf[pos++] = '0';
    } else if (cpu_percent >= 10) {
        cpu_buf[pos++] = '0' + (cpu_percent / 10);
        cpu_buf[pos++] = '0' + (cpu_percent % 10);
    } else {
        cpu_buf[pos++] = '0';
        cpu_buf[pos++] = '0' + cpu_percent;
    }
    cpu_buf[pos++] = '%';
    cpu_buf[pos] = '\0';
    
    m_cpu_label.set_text(cpu_buf);
    
    // Format memory label: "MEM: XX%"
    mem_buf[0] = 'M';
    mem_buf[1] = 'E';
    mem_buf[2] = 'M';
    mem_buf[3] = ':';
    mem_buf[4] = ' ';
    
    // Convert percentage to string
    pos = 5;
    if (mem_percent >= 100) {
        mem_buf[pos++] = '1';
        mem_buf[pos++] = '0';
        mem_buf[pos++] = '0';
    } else if (mem_percent >= 10) {
        mem_buf[pos++] = '0' + (mem_percent / 10);
        mem_buf[pos++] = '0' + (mem_percent % 10);
    } else {
        mem_buf[pos++] = '0';
        mem_buf[pos++] = '0' + mem_percent;
    }
    mem_buf[pos++] = '%';
    mem_buf[pos] = '\0';
    
    m_mem_label.set_text(mem_buf);
}

} // namespace acos::apps
