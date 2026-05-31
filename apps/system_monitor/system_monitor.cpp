#include "system_monitor.h"

namespace acos::apps {

SystemMonitor::SystemMonitor() : gui::WindowWidget("System Monitor", 300, 100, 300, 200),
                                 m_cpu_label("CPU: 0%"), m_mem_label("MEM: 0%") {
    add_child(&m_cpu_label);
    add_child(&m_mem_label);

    m_cpu_label.set_position(320, 140);
    m_mem_label.set_position(320, 170);
}

void SystemMonitor::refresh() {
    // Update stats from kernel
}

} // namespace acos::apps
