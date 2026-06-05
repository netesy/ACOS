#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/text.h>

namespace acos::apps {

class SystemMonitor : public gui::WindowWidget {
public:
    SystemMonitor();
    void refresh();

private:
    gui::Ref<gui::widgets::Text> m_cpu_label;
    gui::Ref<gui::widgets::Text> m_mem_label;
};

} // namespace acos::apps
