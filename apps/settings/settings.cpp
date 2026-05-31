#include "settings.h"

namespace acos::apps {

Settings::Settings() : gui::WindowWidget("Settings", 200, 150, 400, 300),
                       m_display_btn("Display"), m_theme_btn("Theme") {
    add_child(&m_display_btn);
    add_child(&m_theme_btn);

    m_display_btn.set_position(220, 200);
    m_theme_btn.set_position(220, 240);
}

} // namespace acos::apps
