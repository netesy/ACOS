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

void Renderer::blend_circle(u32 xc, u32 yc, u32 r, u32 color, u8 alpha) {
    if (!m_fb) return;
    for (int y = -(int)r; y <= (int)r; y++) {
        for (int x = -(int)r; x <= (int)r; x++) {
            if (x * x + y * y <= (int)(r * r)) {
                int px = (int)xc + x;
                int py = (int)yc + y;
                if (px < 0 || py < 0) continue;
                blend_pixel((u32)px, (u32)py, color, alpha);
            }
        }
    }
}

void Renderer::blend_glass_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 tint, u8 alpha, u32 blur_step) {
    if (!m_fb || w == 0 || h == 0) return;
    if (blur_step == 0) blur_step = 1;

    auto in_rounded = [&](int rx, int ry) -> bool {
        if (rx < 0 || ry < 0 || rx >= (int)w || ry >= (int)h) return false;
        if (radius == 0) return true;
        int cx = -1, cy = -1;
        int rad = (int)radius;
        if (rx < rad && ry < rad) { cx = rad; cy = rad; }
        else if (rx >= (int)w - rad && ry < rad) { cx = (int)w - rad - 1; cy = rad; }
        else if (rx < rad && ry >= (int)h - rad) { cx = rad; cy = (int)h - rad - 1; }
        else if (rx >= (int)w - rad && ry >= (int)h - rad) { cx = (int)w - rad - 1; cy = (int)h - rad - 1; }
        else return true;
        int dx = rx - cx, dy = ry - cy;
        return (dx * dx + dy * dy) <= (rad * rad);
    };

    // Sample offsets for a cheap approximate box blur of the existing backdrop.
    int offs[5][2] = {
        {0, 0},
        {-(int)blur_step, 0}, {(int)blur_step, 0},
        {0, -(int)blur_step}, {0, (int)blur_step}
    };

    u32 fb_w = m_fb->width();
    u32 fb_h = m_fb->height();

    for (u32 j = 0; j < h; j++) {
        for (u32 i = 0; i < w; i++) {
            if (!in_rounded((int)i, (int)j)) continue;

            int px = (int)(x + i), py = (int)(y + j);
            u32 sum_r = 0, sum_g = 0, sum_b = 0, cnt = 0;
            for (auto& o : offs) {
                int sx = px + o[0], sy = py + o[1];
                if (sx < 0 || sy < 0 || sx >= (int)fb_w || sy >= (int)fb_h) continue;
                u32 c = m_fb->get_pixel((u32)sx, (u32)sy);
                sum_r += (c >> 16) & 0xFF;
                sum_g += (c >> 8) & 0xFF;
                sum_b += c & 0xFF;
                cnt++;
            }
            if (cnt == 0) continue;

            u32 br = sum_r / cnt, bg = sum_g / cnt, bb = sum_b / cnt;
            m_fb->put_pixel((u32)px, (u32)py, 0xFF000000 | (br << 16) | (bg << 8) | bb);
            blend_pixel((u32)px, (u32)py, tint, alpha);
        }
    }
}

void Renderer::draw_bitmap(u32 x, u32 y, u32 w, u32 h, const unsigned char* rgba, u32 src_w, u32 src_h) {
    if (!m_fb || !rgba || w == 0 || h == 0 || src_w == 0 || src_h == 0) return;

    for (u32 j = 0; j < h; j++) {
        u32 sy0 = (j * src_h) / h;
        u32 sy1 = ((j + 1) * src_h) / h;
        if (sy1 <= sy0) sy1 = sy0 + 1;
        if (sy1 > src_h) sy1 = src_h;

        for (u32 i = 0; i < w; i++) {
            u32 sx0 = (i * src_w) / w;
            u32 sx1 = ((i + 1) * src_w) / w;
            if (sx1 <= sx0) sx1 = sx0 + 1;
            if (sx1 > src_w) sx1 = src_w;

            u32 sum_r = 0, sum_g = 0, sum_b = 0, sum_a = 0, count = 0;
            for (u32 sy = sy0; sy < sy1; sy++) {
                for (u32 sx = sx0; sx < sx1; sx++) {
                    const unsigned char* p = rgba + (sy * src_w + sx) * 4;
                    sum_r += p[0]; sum_g += p[1]; sum_b += p[2]; sum_a += p[3];
                    count++;
                }
            }
            if (count == 0) continue;

            u8 a = (u8)(sum_a / count);
            if (a == 0) continue;
            u32 r = sum_r / count, g = sum_g / count, b = sum_b / count;
            u32 color = (r << 16) | (g << 8) | b;
            blend_pixel(x + i, y + j, color, a);
        }
    }
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
