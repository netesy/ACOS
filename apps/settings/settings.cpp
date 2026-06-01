#include "settings.h"
#include <userland/gui/theme.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::apps {

Settings::Settings() : gui::WindowWidget("Settings", 200, 150, 400, 300),
                       m_display_btn("Display"), m_theme_btn("Theme") {
    add_child(&m_display_btn);
    add_child(&m_theme_btn);

    m_display_btn.set_position(220, 200);
    m_theme_btn.set_position(220, 240);
    
    // Setup button callbacks
    m_display_btn.set_on_click([this](gui::Button* btn) {
        this->on_display_clicked();
    });
    
    m_theme_btn.set_on_click([this](gui::Button* btn) {
        this->on_theme_clicked();
    });
}

void Settings::on_display_clicked() {
    // Handle display settings
    // In a full implementation, this would:
    // 1. Open display settings dialog
    // 2. Show resolution options
    // 3. Show refresh rate options
    // 4. Apply changes to display server
}

void Settings::on_theme_clicked() {
    // Handle theme settings
    // In a full implementation, this would:
    // 1. Open theme selection dialog
    // 2. Show available themes (Default, Dark, Light)
    // 3. Apply selected theme
    // 4. Update all windows with new theme
    
    // For now, cycle through themes
    static int current_theme = 0;
    
    switch (current_theme) {
        case 0:
            acos::gui::init_default_theme();
            break;
        case 1:
            acos::gui::init_dark_theme();
            break;
        case 2:
            acos::gui::init_light_theme();
            break;
    }
    
    current_theme = (current_theme + 1) % 3;
}

} // namespace acos::apps
