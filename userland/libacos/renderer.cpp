#include <acos/renderer.h>
#include <acos/font_manager.h>
#include <acos/font.h>

namespace acos::graphics {

Renderer::Renderer(Framebuffer* fb) : m_fb(fb) {}

void Renderer::draw_pixel(u32 x, u32 y, u32 color) {
    if (m_fb) m_fb->put_pixel(x, y, color);
}

void Renderer::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    if (m_fb) m_fb->fill_rect(x, y, w, h, color);
}

void Renderer::blend_pixel(u32 x, u32 y, u32 color, u8 alpha) {
    if (!m_fb) return;
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

void Renderer::draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    if (!m_fb) return;
    for (u32 i = 0; i < w; i++) {
        m_fb->put_pixel(x + i, y, color);
        m_fb->put_pixel(x + i, y + h - 1, color);
    }
    for (u32 i = 0; i < h; i++) {
        m_fb->put_pixel(x, y + i, color);
        m_fb->put_pixel(x + w - 1, y + i, color);
    }
}

void Renderer::draw_line(u32 x0, u32 y0, u32 x1, u32 y1, u32 color) {
    if (!m_fb) return;
    int dx = (int)x1 - (int)x0;
    int dy = (int)y1 - (int)y0;
    int abs_dx = dx < 0 ? -dx : dx;
    int abs_dy = dy < 0 ? -dy : dy;
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = abs_dx - abs_dy;

    while (true) {
        m_fb->put_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -abs_dy) {
            err -= abs_dy;
            x0 += sx;
        }
        if (e2 < abs_dx) {
            err += abs_dx;
            y0 += sy;
        }
    }
}

void Renderer::draw_circle(u32 xc, u32 yc, u32 r, u32 color) {
    if (!m_fb) return;
    int x = 0, y = r;
    int d = 3 - 2 * r;
    auto draw_symmetric = [&](u32 x, u32 y) {
        m_fb->put_pixel(xc + x, yc + y, color);
        m_fb->put_pixel(xc - x, yc + y, color);
        m_fb->put_pixel(xc + x, yc - y, color);
        m_fb->put_pixel(xc - x, yc - y, color);
        m_fb->put_pixel(xc + y, yc + x, color);
        m_fb->put_pixel(xc - y, yc + x, color);
        m_fb->put_pixel(xc + y, yc - x, color);
        m_fb->put_pixel(xc - y, yc - x, color);
    };

    while (y >= x) {
        draw_symmetric(x, y);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void Renderer::fill_circle(u32 xc, u32 yc, u32 r, u32 color) {
    if (!m_fb) return;
    for (int y = -(int)r; y <= (int)r; y++) {
        for (int x = -(int)r; x <= (int)r; x++) {
            if (x * x + y * y <= (int)(r * r)) {
                m_fb->put_pixel(xc + x, yc + y, color);
            }
        }
    }
}

void Renderer::blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha) {
    if (!m_fb) return;
    for (u32 j = 0; j < h; j++) {
        for (u32 i = 0; i < w; i++) {
            blend_pixel(x + i, y + j, color, alpha);
        }
    }
}

void Renderer::draw_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 r, u32 color) {
    if (!m_fb) return;
    for (u32 i = r; i < w - r; i++) {
        m_fb->put_pixel(x + i, y, color);
        m_fb->put_pixel(x + i, y + h - 1, color);
    }
    for (u32 i = r; i < h - r; i++) {
        m_fb->put_pixel(x, y + i, color);
        m_fb->put_pixel(x + w - 1, y + i, color);
    }
}

void Renderer::fill_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 r, u32 color) {
    if (!m_fb) return;
    m_fb->fill_rect(x + r, y, w - 2 * r, h, color);
    m_fb->fill_rect(x, y + r, r, h - 2 * r, color);
    m_fb->fill_rect(x + w - r, y + r, r, h - 2 * r, color);
    fill_circle(x + r, y + r, r, color);
    fill_circle(x + w - r - 1, y + r, r, color);
    fill_circle(x + r, y + h - r - 1, r, color);
    fill_circle(x + w - r - 1, y + h - r - 1, r, color);
}

void Renderer::draw_text(const char* text, u32 x, u32 y, u32 color) {
    if (!m_fb) return;
    const Font* font = FontManager::get_ui_font();
    if (!font) return;

    u32 cur_x = x;
    while (*text) {
        char c = *text++;
        if (c == '\n') {
            cur_x = x;
            y += font->height();
            continue;
        }

        const u8* glyph = font->get_glyph(c);
        if (glyph) {
            for (u32 gy = 0; gy < font->height(); gy++) {
                for (u32 gx = 0; gx < font->width(); gx++) {
                    u32 bit = 1 << (font->width() - 1 - gx);
                    if (glyph[gy] & bit) {
                        m_fb->put_pixel(cur_x + gx, y + gy, color);
                    }
                }
            }
        }
        cur_x += font->width();
    }
}

void Renderer::measure_text(const char* text, u32& w, u32& h) {
    const Font* font = FontManager::get_ui_font();
    if (!font) {
        w = 0; h = 0;
        return;
    }

    w = 0;
    h = font->height();
    u32 max_w = 0;
    u32 cur_w = 0;

    while (*text) {
        char c = *text++;
        if (c == '\n') {
            if (cur_w > max_w) max_w = cur_w;
            cur_w = 0;
            h += font->height();
            continue;
        }
        cur_w += font->width();
    }
    if (cur_w > max_w) max_w = cur_w;
    w = max_w;
}

void Renderer::draw_shadow(u32 x, u32 y, u32 w, u32 h, u32 offset, u8 alpha) {
    blend_rect(x + offset, y + offset, w, h, 0x000000, alpha);
}

} // namespace acos::graphics
