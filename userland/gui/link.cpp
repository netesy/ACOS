#include "link.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Link::Link(const char* text) : Label(text) {
    m_rect.h = 20;
    m_flags |= (u32)WidgetFlags::Clickable;
}

void Link::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    u32 color = (m_state == WidgetState::Hovered) ? g_current_theme.secondary : g_current_theme.primary;
    m_text_color = color;

    Label::draw(renderer);

    // Draw underline
    u32 tx = (u32)m_rect.x;
    if (m_alignment == TextAlignment::Center) tx += m_rect.w / 2 - 40; // Approx
    renderer->draw_line(tx, m_rect.y + m_rect.h - 2, tx + 80, m_rect.y + m_rect.h - 2, color);
}

void Link::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (hit_test(mx, my)) {
            m_state = WidgetState::Hovered;
            if (pressed) on_clicked.emit();
        } else {
            m_state = WidgetState::Normal;
        }
    }
}

} // namespace acos::gui
