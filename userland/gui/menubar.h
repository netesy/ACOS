#pragma once
#include "widget.h"
#include "menu.h"

namespace acos::gui {

class MenuBar : public Widget {
public:
    MenuBar();
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    Menu* add_menu(const char* title);

private:
    const char* m_titles[8];
    Menu* m_menus[8];
    u32 m_count;
    i32 m_active_menu;
};

} // namespace acos::gui
