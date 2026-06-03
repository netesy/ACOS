#include "menubar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

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

void MenuBar::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 240);
    renderer->draw_line(m_rect.x, m_rect.y + m_rect.h, m_rect.x + m_rect.w, m_rect.y + m_rect.h, g_current_theme.border);

    i32 cur_x = m_rect.x + 10;
    for (u32 i = 0; i < m_count; i++) {
        if (m_active_menu == (i32)i) {
            renderer->blend_rect(cur_x - 5, m_rect.y + 2, 70, m_rect.h - 4, g_current_theme.primary, 80);
        }
        renderer->draw_text(m_titles[i], cur_x, m_rect.y + 6, g_current_theme.text);

        if (m_menus[i]->is_visible()) {
            m_menus[i]->set_position(cur_x - 5, m_rect.y + m_rect.h);
            m_menus[i]->draw(renderer);
        }
        cur_x += 80;
    }
}

void MenuBar::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (pressed && my >= m_rect.y && my < m_rect.y + 30) {
            i32 idx = (mx - m_rect.x - 10) / 80;
            if (idx >= 0 && idx < (i32)m_count) {
                if (m_active_menu == idx) {
                    m_menus[idx]->set_visible(false);
                    m_active_menu = -1;
                } else {
                    if (m_active_menu != -1) m_menus[m_active_menu]->set_visible(false);
                    m_active_menu = idx;
                    m_menus[idx]->set_visible(true);
                }
            }
        }
    }
    if (m_active_menu != -1) m_menus[m_active_menu]->handle_event(event);
}

} // namespace acos::gui
