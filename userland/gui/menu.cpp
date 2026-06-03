#include "menu.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

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

void Menu::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    draw_shadow(renderer);
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 240);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, g_current_theme.border);

    for (u32 i = 0; i < m_count; i++) {
        i32 iy = m_rect.y + 5 + i * 24;
        if (m_hovered_index == (i32)i) {
            renderer->blend_rect(m_rect.x + 2, iy, m_rect.w - 4, 24, g_current_theme.primary, 100);
        }
        renderer->draw_text(m_items[i], (u32)m_rect.x + 10, (u32)iy + 4, g_current_theme.text);
    }
}

void Menu::handle_event(const acos::input::InputEvent& event) {
    if (!is_visible()) return;
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (hit_test(mx, my)) {
            m_hovered_index = (my - m_rect.y - 5) / 24;
            if (pressed && m_hovered_index >= 0 && m_hovered_index < (i32)m_count) {
                on_item_selected.emit(m_hovered_index);
                set_visible(false);
            }
        } else {
            m_hovered_index = -1;
            if (pressed) set_visible(false);
        }
    }
}

} // namespace acos::gui
