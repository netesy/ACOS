#include <kernel/graphics/renderer.h>

namespace acos::graphics {

Renderer::Renderer(Framebuffer* fb) : m_fb(fb) {}

void Renderer::draw_pixel(u32 x, u32 y, u32 color) {
    m_fb->put_pixel(x, y, color);
}

void Renderer::draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    (void)x1; (void)y1; (void)x2; (void)y2; (void)color;
    // Bresenham's logic placeholder
}

void Renderer::draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    for (u32 i = x; i < x + w; ++i) {
        draw_pixel(i, y, color);
        draw_pixel(i, y + h - 1, color);
    }
    for (u32 i = y; i < y + h; ++i) {
        draw_pixel(x, i, color);
        draw_pixel(x + w - 1, i, color);
    }
}

void Renderer::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    m_fb->fill_rect(x, y, w, h, color);
}

void Renderer::draw_text(const char* text, u32 x, u32 y, u32 color) {
    (void)text; (void)x; (void)y; (void)color;
    // Glyph rendering logic
}

} // namespace acos::graphics
