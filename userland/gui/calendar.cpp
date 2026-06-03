#include "calendar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Calendar::Calendar() : m_year(2026), m_month(6), m_selected_day(2) {
    m_rect.w = 200;
    m_rect.h = 220;
}

void Calendar::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 180);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 8, g_current_theme.border);

    renderer->draw_text("June 2026", m_rect.x + 50, m_rect.y + 10, g_current_theme.primary, acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Bold);

    const char* days[] = {"S", "M", "T", "W", "T", "F", "S"};
    for (int i = 0; i < 7; i++) {
        renderer->draw_text(days[i], m_rect.x + 10 + i * 26, m_rect.y + 40, g_current_theme.text_secondary);
    }

    // Static June 2026 grid
    int day = 1;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 7; c++) {
            if (r == 0 && c < 1) continue; // Starts on Monday
            if (day > 30) break;

            i32 dx = m_rect.x + 10 + c * 26;
            i32 dy = m_rect.y + 70 + r * 26;

            if (day == (int)m_selected_day) {
                renderer->fill_circle(dx + 8, dy + 8, 12, g_current_theme.primary);
            }

            char buf[3];
            buf[0] = (day / 10) ? (day / 10 + '0') : (day + '0');
            if (day / 10) { buf[1] = (day % 10 + '0'); buf[2] = '\0'; }
            else { buf[1] = '\0'; }

            renderer->draw_text(buf, dx + 4, dy, (day == (int)m_selected_day) ? 0xFF000000 : g_current_theme.text);
            day++;
        }
    }
}

void Calendar::handle_event(const acos::input::InputEvent& event) { (void)event; }

} // namespace acos::gui
