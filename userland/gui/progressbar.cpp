#include "progressbar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ProgressBar::ProgressBar() : m_value(0.0f), m_min(0.0f), m_max(100.0f) {
    m_rect.w = 200;
    m_rect.h = 12;
}

ProgressBar::~ProgressBar() {}

void ProgressBar::set_value(float value) {
    if (value < m_min) m_value = m_min;
    else if (value > m_max) m_value = m_max;
    else m_value = value;
}

void ProgressBar::set_range(float min, float max) {
    m_min = min;
    m_max = max;
    set_value(m_value);
}

void ProgressBar::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    // Background track
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 100);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.h / 2, g_current_theme.border);

    // Active progress fill
    float ratio = (m_value - m_min) / (m_max - m_min);
    u32 fill_w = static_cast<u32>(m_rect.w * ratio);

    if (fill_w > 0) {
        acos::graphics::Gradient grad;
        grad.start = acos::graphics::Color::from_argb(g_current_theme.primary);
        grad.end = acos::graphics::Color::from_argb(g_current_theme.secondary);
        grad.horizontal = true;

        renderer->draw_gradient_rect(m_rect.x, m_rect.y, fill_w, m_rect.h, grad);

        // Add a subtle glow pulse effect (simulated by a higher alpha layer)
        renderer->blend_rect(m_rect.x, m_rect.y, fill_w, m_rect.h, g_current_theme.primary, 40);
    }
}

} // namespace acos::gui
