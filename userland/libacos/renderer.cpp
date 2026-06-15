#include <acos/renderer.h>

namespace acos::graphics {

Renderer::Renderer(Framebuffer* fb) : m_fb(fb) {}

void Renderer::draw_pixel(u32 x, u32 y, u32 color) {
    m_fb->put_pixel(x, y, color);
}

void Renderer::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    m_fb->fill_rect(x, y, w, h, color);
}

void Renderer::blend_pixel(u32 x, u32 y, u32 color, u8 alpha) {
    if (alpha == 255) {
        m_fb->put_pixel(x, y, color);
        return;
    }
    if (alpha == 0) return;

    u32 bg = m_fb->get_pixel(x, y);
    u32 rb = (color & 0xFF00FF) * alpha + (bg & 0xFF00FF) * (255 - alpha);
    u32 g = (color & 0x00FF00) * alpha + (bg & 0x00FF00) * (255 - alpha);
    u32 blended = ((rb >> 8) & 0xFF00FF) | ((g >> 8) & 0x00FF00);

    m_fb->put_pixel(x, y, 0xFF000000 | blended);
}

} // namespace acos::graphics
