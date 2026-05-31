#include "button.h"
#include "theme.h"

namespace acos::gui {

Button::Button(const char* label) : m_label(label), m_on_click(nullptr), m_pressed(false) {
    m_rect.w = 80;
    m_rect.h = 30;
}

void Button::draw(u32* buffer, u32 pitch) {
    u32 color = m_pressed ? g_current_theme.accent : g_current_theme.widget_bg;
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = color;
        }
    }
    // In a real implementation, we would draw the label here
}

void Button::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        // Simple hit testing
        // Assuming event.code 0 is X, 1 is Y, 2 is button
        // For a more robust system, we'd need mouse state
    }
}

} // namespace acos::gui
