#include "menuitem.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

MenuItem::MenuItem(const char* label) : m_label(label) {
    m_rect.h = 24;
}

void MenuItem::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;
    if (m_state == WidgetState::Hovered) {
        renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.primary, 100);
    }
    renderer->draw_text(m_label, m_rect.x + 10, m_rect.y + 4, g_current_theme.text);
}

void MenuItem::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (hit_test(mx, my)) {
            m_state = WidgetState::Hovered;
            if (pressed) on_triggered.emit();
        } else {
            m_state = WidgetState::Normal;
        }
    }
}

} // namespace acos::gui
