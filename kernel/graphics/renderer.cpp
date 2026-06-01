#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

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
    u32 cur_y = y;
    while (*text) {
        const char c = *text++;
        if (c == '\n') {
            cur_x = x;
            cur_y += 10;
            continue;
        }
        if (c == ' ') {
            cur_x += 8;
            continue;
        }
        for (u32 row = 0; row < 8; ++row) {
            for (u32 col = 0; col < 8; ++col) {
                const u8 pattern = static_cast<u8>((static_cast<u8>(c) >> ((row + col) & 3)) ^
                                                   (static_cast<u8>(c) << ((row ^ col) & 1)));
                if (row == 0 || row == 7 || col == 0 || col == 7 || ((pattern >> (col & 7)) & 1U)) {
                    draw_pixel(cur_x + col, cur_y + row, color);
                }
            }
        }
        cur_x += 8;
    }
}

} // namespace acos::graphics

namespace acos::graphics {

void Renderer::draw_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    i32 x = static_cast<i32>(radius);
    i32 y = 0;
    i32 err = 0;
    while (x >= y) {
        draw_pixel(cx + x, cy + y, color);
        draw_pixel(cx + y, cy + x, color);
        draw_pixel(cx - y, cy + x, color);
        draw_pixel(cx - x, cy + y, color);
        draw_pixel(cx - x, cy - y, color);
        draw_pixel(cx - y, cy - x, color);
        draw_pixel(cx + y, cy - x, color);
        draw_pixel(cx + x, cy - y, color);
        ++y;
        if (err <= 0) err += 2 * y + 1;
        if (err > 0) { --x; err -= 2 * x + 1; }
    }
}

void Renderer::fill_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    for (i32 y = -static_cast<i32>(radius); y <= static_cast<i32>(radius); ++y) {
        for (i32 x = -static_cast<i32>(radius); x <= static_cast<i32>(radius); ++x) {
            if (x * x + y * y <= static_cast<i32>(radius * radius)) {
                draw_pixel(static_cast<u32>(static_cast<i32>(cx) + x), static_cast<u32>(static_cast<i32>(cy) + y), color);
            }
        }
    }
}

void Renderer::draw_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color) {
    (void)radius;
    draw_rect(x, y, w, h, color);
}

void Renderer::fill_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color) {
    (void)radius;
    fill_rect(x, y, w, h, color);
}

void Renderer::draw_gradient_rect(u32 x, u32 y, u32 w, u32 h, const Gradient& grad) {
    const u32 top = grad.start.to_argb();
    const u32 bottom = grad.end.to_argb();
    for (u32 row = 0; row < h; ++row) {
        const u32 color = (row < h / 2) ? top : bottom;
        fill_rect(x, y + row, w, 1, color);
    }
}

void Renderer::draw_border(u32 x, u32 y, u32 w, u32 h, u32 color, u32 thickness) {
    for (u32 i = 0; i < thickness; ++i) {
        draw_rect(x + i, y + i, w - (i * 2), h - (i * 2), color);
    }
}

void Renderer::blend_pixel(u32 x, u32 y, u32 color, u8 alpha) {
    (void)alpha;
    draw_pixel(x, y, color);
}

void Renderer::blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha) {
    (void)alpha;
    fill_rect(x, y, w, h, color);
}

void Renderer::draw_shadow(u32 x, u32 y, u32 w, u32 h, u32 offset, u8 alpha) {
    blend_rect(x + offset, y + offset, w, h, 0xFF000000, alpha);
}

void Renderer::set_clip_rect(const ClipRect& rect) {
    (void)rect;
}

void Renderer::clear_clip_rect() {}

} // namespace acos::graphics
