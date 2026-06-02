#include "combobox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ComboBox::ComboBox() : m_expanded(false), m_current_text("Select...") {
    m_rect.w = 150;
    m_rect.h = 28;
    m_popup.set_visible(false);
}

ComboBox::~ComboBox() {}

void ComboBox::add_item(const char* item) {
    m_popup.add_item(item);
}

const char* ComboBox::selected_item() const {
    return m_current_text;
}

void ComboBox::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 200);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, g_current_theme.border);
    renderer->draw_text(m_current_text, m_rect.x + 8, m_rect.y + 6, g_current_theme.text);

    // Dropdown arrow
    renderer->draw_line(m_rect.x + m_rect.w - 20, m_rect.y + 10, m_rect.x + m_rect.w - 12, m_rect.y + 10, g_current_theme.text);
    renderer->draw_line(m_rect.x + m_rect.w - 16, m_rect.y + 18, m_rect.x + m_rect.w - 12, m_rect.y + 10, g_current_theme.text);

    if (m_expanded) {
        m_popup.set_position(m_rect.x, m_rect.y + m_rect.h);
        m_popup.set_size(m_rect.w, 100);
        m_popup.draw(renderer);
    }
}

void ComboBox::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (pressed) {
            if (hit_test(mx, my)) {
                m_expanded = !m_expanded;
            } else if (m_expanded) {
                // Check if hit in popup (simplified)
                m_expanded = false;
            }
        }
    }
    if (m_expanded) m_popup.handle_event(event);
}

} // namespace acos::gui
