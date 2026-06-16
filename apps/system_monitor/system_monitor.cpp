#include <acos/process.h>
#include <acos/runtime.h>
#include "system_monitor.h"
#include <acos/process.h>
#include <userland/gui/core/context.h>

namespace acos::apps {

static void format_percent(char* buf, const char* prefix, u32 percent) {
    usize i = 0;
    while (prefix[i]) { buf[i] = prefix[i]; i++; }
    buf[i++] = ' ';

    if (percent >= 100) {
        buf[i++] = '1'; buf[i++] = '0'; buf[i++] = '0';
    } else if (percent >= 10) {
        buf[i++] = '0' + (percent / 10);
        buf[i++] = '0' + (percent % 10);
    } else {
        buf[i++] = '0' + percent;
    }
    buf[i++] = '%';
    buf[i] = '\0';
}

SystemMonitor::SystemMonitor() : gui::WindowWidget("System Monitor", 300, 100, 300, 200) {
    auto& region = gui::UIContext::get().region();
    m_cpu_label = region.alloc<gui::widgets::Text>("CPU: 0%");
    m_mem_label = region.alloc<gui::widgets::Text>("MEM: 0%");

    m_cpu_label->set_position(20, 40);
    m_mem_label->set_position(20, 70);

    add_child(m_cpu_label.static_cast_to<gui::Widget>());
    add_child(m_mem_label.static_cast_to<gui::Widget>());
}

void SystemMonitor::refresh() {
    usize total_threads = acos::scheduler::get_thread_count();
    usize running_threads = acos::scheduler::get_running_thread_count();
    u32 cpu_percent = (running_threads * 100) / (total_threads > 0 ? total_threads : 1);
    if (cpu_percent > 100) cpu_percent = 100;
    
    u64 total_memory = acos::memory::pmm_get_total_memory();
    u64 used_memory = acos::memory::pmm_get_used_memory();
    u32 mem_percent = total_memory > 0 ? (u32)((used_memory * 100) / total_memory) : 0;
    if (mem_percent > 100) mem_percent = 100;
    
    char cpu_buf[32];
    char mem_buf[32];
    format_percent(cpu_buf, "CPU:", cpu_percent);
    format_percent(mem_buf, "MEM:", mem_percent);

    if (m_cpu_label) m_cpu_label->set_text(cpu_buf);
    if (m_mem_label) m_mem_label->set_text(mem_buf);
}

} // namespace acos::apps
