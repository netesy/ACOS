#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/label.h>

namespace acos::apps {

class SystemMonitor : public gui::WindowWidget {
public:
    SystemMonitor();
    void refresh();

private:
    gui::Label m_cpu_label;
    gui::Label m_mem_label;
};

} // namespace acos::apps
