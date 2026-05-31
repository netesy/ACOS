#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/button.h>

namespace acos::apps {

class Settings : public gui::WindowWidget {
public:
    Settings();

private:
    gui::Button m_display_btn;
    gui::Button m_theme_btn;
};

} // namespace acos::apps
