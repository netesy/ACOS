#include <acos/framebuffer.h>

namespace acos::graphics {

Framebuffer::Framebuffer(u64 base, u64 size, u32 width, u32 height, u32 pitch, u32 bpp)
    : m_base(base), m_size(size), m_width(width), m_height(height), m_pitch(pitch), m_bpp(bpp) {}

void Framebuffer::put_pixel(u32 x, u32 y, u32 color) {
    if (x >= m_width || y >= m_height) return;
    u32* fb = reinterpret_cast<u32*>(m_base);
    fb[y * m_pitch + x] = color;
}

u32 Framebuffer::get_pixel(u32 x, u32 y) const {
    if (x >= m_width || y >= m_height) return 0;
    const u32* fb = reinterpret_cast<const u32*>(m_base);
    return fb[y * m_pitch + x];
}

void Framebuffer::clear(u32 color) {
    fill_rect(0, 0, m_width, m_height, color);
}

void Framebuffer::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    for (u32 i = y; i < y + h && i < m_height; ++i) {
        for (u32 j = x; j < x + w && j < m_width; ++j) {
            put_pixel(j, i, color);
        }
    }
}

} // namespace acos::graphics
