#include "icon.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Icon::Icon(IconType type) : m_type(type), m_color(g_current_theme.primary), m_active(false) {
    m_rect.w = 32;
    m_rect.h = 32;
}

Icon::~Icon() {}


void Icon::draw_terminal(acos::graphics::Renderer* renderer) {
    renderer->draw_rounded_rect(m_rect.x + 2, m_rect.y + 4, m_rect.w - 4, m_rect.h - 8, 4, m_color);
    renderer->draw_line(m_rect.x + 6, m_rect.y + 10, m_rect.x + 12, m_rect.y + 16, m_color);
    renderer->draw_line(m_rect.x + 6, m_rect.y + 22, m_rect.x + 12, m_rect.y + 16, m_color);
    renderer->draw_line(m_rect.x + 14, m_rect.y + 24, m_rect.x + 24, m_rect.y + 24, m_color);
}

void Icon::draw_files(acos::graphics::Renderer* renderer) {
    renderer->draw_line(m_rect.x + 4, m_rect.y + 6, m_rect.x + 12, m_rect.y + 6, m_color);
    renderer->draw_line(m_rect.x + 12, m_rect.y + 6, m_rect.x + 16, m_rect.y + 10, m_color);
    renderer->draw_line(m_rect.x + 16, m_rect.y + 10, m_rect.x + 28, m_rect.y + 10, m_color);
    renderer->draw_line(m_rect.x + 28, m_rect.y + 10, m_rect.x + 28, m_rect.y + 26, m_color);
    renderer->draw_line(m_rect.x + 28, m_rect.y + 26, m_rect.x + 4, m_rect.y + 26, m_color);
    renderer->draw_line(m_rect.x + 4, m_rect.y + 26, m_rect.x + 4, m_rect.y + 6, m_color);
}

void Icon::draw_settings(acos::graphics::Renderer* renderer) {
    renderer->draw_circle(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2, 8, m_color);
    renderer->draw_circle(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2, 3, m_color);
    for (int i = 0; i < 8; i++) {
        // Cog teeth - simplified
        renderer->draw_line(m_rect.x + 16, m_rect.y + 4, m_rect.x + 16, m_rect.y + 8, m_color);
    }
}

void Icon::draw_code(acos::graphics::Renderer* renderer) {
    renderer->draw_line(m_rect.x + 10, m_rect.y + 8, m_rect.x + 4, m_rect.y + 16, m_color);
    renderer->draw_line(m_rect.x + 4, m_rect.y + 16, m_rect.x + 10, m_rect.y + 24, m_color);
    renderer->draw_line(m_rect.x + 22, m_rect.y + 8, m_rect.x + 28, m_rect.y + 16, m_color);
    renderer->draw_line(m_rect.x + 28, m_rect.y + 16, m_rect.x + 22, m_rect.y + 24, m_color);
    renderer->draw_line(m_rect.x + 20, m_rect.y + 6, m_rect.x + 12, m_rect.y + 26, m_color);
}

Ref<RenderObject> Icon::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
