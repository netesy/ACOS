#include <kernel/graphics/renderer.h>

namespace acos::graphics {

Renderer::Renderer(Framebuffer* fb) : m_fb(fb) {}

void Renderer::draw_pixel(u32 x, u32 y, u32 color) {
    m_fb->put_pixel(x, y, color);
}

void Renderer::draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    i32 dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    i32 dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
    i32 sx = (x1 < x2) ? 1 : -1;
    i32 sy = (y1 < y2) ? 1 : -1;
    i32 err = dx - dy;
    
    i32 x = x1, y = y1;
    while (true) {
        draw_pixel(x, y, color);
        
        if (x == (i32)x2 && y == (i32)y2) break;
        
        i32 e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
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
    if (!text) return;
    
    u32 cur_x = x;
    while (*text) {
        Font::draw_char(*text, cur_x, y, color);
        cur_x += 8;
        text++;
    }
}

} // namespace acos::graphics
