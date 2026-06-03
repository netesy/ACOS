#include "toast.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Toast::Toast(const char* message) : m_message(message), m_timer(0), m_duration(0), m_alpha(0) {
    m_rect = {300, 500, 200, 40};
    set_visible(false);
}

void Toast::show(u32 duration_ms) {
    m_duration = duration_ms;
    m_timer = 0;
    m_alpha = 255;
    set_visible(true);
}

void Toast::update(u64 delta_ms) {
    if (!is_visible()) return;
    m_timer += delta_ms;
    if (m_timer > m_duration) {
        set_visible(false);
    } else if (m_timer > m_duration - 500) {
        // Fade out
        m_alpha = (u8)(255 * (m_duration - m_timer) / 500);
    }
}

void Toast::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    renderer->draw_shadow(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, (u8)(m_alpha / 2));
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF333333, (u8)(m_alpha * 0.9f));
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 20, g_current_theme.primary);
    renderer->draw_text(m_message, m_rect.x + 20, m_rect.y + 12, 0xFFFFFFFF);
}

} // namespace acos::gui
