#pragma once
#include <window_widget.h>
#include <label.h>

namespace acos::apps {

class SystemMonitor : public ui::WindowWidget {
public:
    SystemMonitor();
    void refresh();

private:
    ui::Label m_cpu_label;
    ui::Label m_mem_label;
};

} // namespace acos::apps
