#include "menubar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

MenuBar::MenuBar() : m_count(0), m_active_menu(-1) {
    m_rect.h = 30;
}

Menu* MenuBar::add_menu(const char* title) {
    if (m_count < 8) {
        m_titles[m_count] = title;
        m_menus[m_count] = new Menu();
        m_menus[m_count]->set_visible(false);
        return m_menus[m_count++];
    }
    return nullptr;
}



Ref<RenderObject> Menubar::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> MenuBar::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
