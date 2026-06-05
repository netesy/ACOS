#include "compositor_engine.h"

namespace acos::gui {

void SoftwareCompositor::composite() {
    if (!m_display_buffer) return;

    // Clear display buffer (or draw background)
    for (u32 i = 0; i < m_width * m_height; i++) m_display_buffer[i] = 0xFF000000;

    for (auto* layer : m_layers) {
        if (!layer || !layer->surface()) continue;

        SoftwareSurface* surface = layer->surface();
        u32* src = surface->buffer();
        i32 lx = layer->x();
        i32 ly = layer->y();
        u32 lw = surface->width();
        u32 lh = surface->height();
        float opacity = layer->opacity();

        for (u32 y = 0; i32(y) < i32(lh); y++) {
            i32 dy = ly + y;
            if (dy < 0 || dy >= (i32)m_height) continue;

            for (u32 x = 0; i32(x) < i32(lw); x++) {
                i32 dx = lx + x;
                if (dx < 0 || dx >= (i32)m_width) continue;

                u32 pixel = src[y * lw + x];
                u32 dst = m_display_buffer[dy * m_width + dx];
                m_display_buffer[dy * m_width + dx] = blend(dst, pixel, opacity);
            }
        }
    }
}

u32 SoftwareCompositor::blend(u32 dst, u32 src, float opacity) {
    u8 sa = (u8)(((src >> 24) & 0xFF) * opacity);
    if (sa == 255) return src;
    if (sa == 0) return dst;

    u8 sr = (src >> 16) & 0xFF;
    u8 sg = (src >> 8) & 0xFF;
    u8 sb = src & 0xFF;

    u8 da = (dst >> 24) & 0xFF;
    u8 dr = (dst >> 16) & 0xFF;
    u8 dg = (dst >> 8) & 0xFF;
    u8 db = dst & 0xFF;

    u32 r = (sr * sa + dr * (255 - sa)) / 255;
    u32 g = (sg * sa + dg * (255 - sa)) / 255;
    u32 b = (sb * sa + db * (255 - sa)) / 255;
    u32 a = (sa * 255 + da * (255 - sa)) / 255;

    return (a << 24) | (r << 16) | (g << 8) | b;
}

} // namespace acos::gui
