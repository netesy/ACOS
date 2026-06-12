#include <acos/process.h>
#include <acos/runtime.h>
#include "menubar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

MenuBar::MenuBar() : m_count(0), m_active_menu(-1) {
    m_rect = {0, 0, 800, 24};
}

MenuBar::~MenuBar() {}

Ref<RenderObject> MenuBar::create_render_object() {
    return Ref<RenderObject>();
}

Menu* MenuBar::add_menu(const char* title) {
    if (m_count < 8) {
        m_titles[m_count] = title;
        // m_menus[m_count] = ...
        return nullptr;
    }
    return nullptr;
}

} // namespace acos::gui::widgets
