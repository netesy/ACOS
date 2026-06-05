#pragma once
#include "widget.h"
#include "menu.h"

namespace acos::gui::widgets {

class MenuBar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    MenuBar();

    Menu* add_menu(const char* title);

private:
    const char* m_titles[8];
    Menu* m_menus[8];
    u32 m_count;
    i32 m_active_menu;
};

} // namespace acos::gui::widgets
