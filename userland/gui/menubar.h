#pragma once
#include "widget.h"
#include "menu.h"

namespace acos::gui::widgets {

class MenuBar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    MenuBar();
    virtual ~MenuBar();

    Menu* add_menu(const char* title);

private:
    [[maybe_unused]] const char* m_titles[8];
    [[maybe_unused]] Menu* m_menus[8];
    ::acos::u32 m_count;
    [[maybe_unused]] ::acos::i32 m_active_menu;
};

} // namespace acos::gui::widgets
