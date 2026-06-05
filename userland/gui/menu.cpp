#include "menu.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Menu::Menu() : m_count(0), m_hovered_index(-1) {
    m_rect.w = 150;
    m_rect.h = 0;
    m_elevation = 12;
}

Menu::~Menu() {}

void Menu::add_item(const char* label) {
    if (m_count < 16) {
        m_items[m_count++] = label;
        m_rect.h = m_count * 24 + 10;
    }
}



Ref<RenderObject> Menu::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
