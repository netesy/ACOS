#pragma once
#include <window_widget.h>
#include <button.h>

namespace acos::apps {

class Settings : public ui::WindowWidget {
public:
    Settings();

private:
    ui::Button m_display_btn;
    ui::Button m_theme_btn;
    
    void on_display_clicked();
    void on_theme_clicked();
};

} // namespace acos::apps
