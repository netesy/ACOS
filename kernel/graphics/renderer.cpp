#include "renderer.h"
#include "font.h"
#include "types.h"

namespace acos::graphics {

namespace {
template <typename T>
T abs(T v) { return v < 0 ? -v : v; }

template <typename T>
void swap(T& a, T& b) { T tmp = a; a = b; b = tmp; }

float sqrt(float x) {
    if (x < 0) return 0;
    float z = 1.0f;
    for (int i = 0; i < 10; i++) {
        z -= (z * z - x) / (2 * z);
    }
    return z;
}
}

Renderer::Renderer(Framebuffer* fb, Surface* surface)
    : m_fb(fb), m_surface(surface), m_clip_enabled(false) {}

void Renderer::draw_pixel(u32 x, u32 y, u32 color) {
    if (is_clipped(x, y)) return;
    if (m_fb) {
        m_fb->put_pixel(x, y, color);
    } else if (m_surface && m_surface->buffer()) {
        m_surface->buffer()[y * m_surface->width() + x] = color;
    }
}

u32 Renderer::get_pixel(u32 x, u32 y) const {
    if (x >= width() || y >= height()) return 0;
    if (m_fb) {
        return m_fb->get_pixel(x, y);
    } else if (m_surface && m_surface->buffer()) {
        return m_surface->buffer()[y * m_surface->width() + x];
    }
    return 0;
}

void Renderer::blend_pixel(u32 x, u32 y, u32 color, u8 alpha) {
    if (is_clipped(x, y)) return;
    if (alpha == 255) {
        draw_pixel(x, y, color);
        return;
    }
    if (alpha == 0) return;

    u32 bg = get_pixel(x, y);
    u32 rb = (color & 0xFF00FF) * alpha + (bg & 0xFF00FF) * (255 - alpha);
    u32 g = (color & 0x00FF00) * alpha + (bg & 0x00FF00) * (255 - alpha);
    u32 blended = ((rb >> 8) & 0xFF00FF) | ((g >> 8) & 0x00FF00);

    draw_pixel(x, y, 0xFF000000 | blended);
}

void Renderer::draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    i32 x1_i = (i32)x1, y1_i = (i32)y1, x2_i = (i32)x2, y2_i = (i32)y2;
    bool steep = abs(y2_i - y1_i) > abs(x2_i - x1_i);
    if (steep) {
        swap(x1_i, y1_i);
        swap(x2_i, y2_i);
    }
    if (x1_i > x2_i) {
        swap(x1_i, x2_i);
        swap(y1_i, y2_i);
    }

    auto plot = [&](int x, int y, float brightness) {
        if (steep) blend_pixel(y, x, color, (u8)(brightness * 255));
        else blend_pixel(x, y, color, (u8)(brightness * 255));
    };

    i32 dx = x2_i - x1_i;
    i32 dy = y2_i - y1_i;
    float gradient = (dx == 0) ? 1.0f : (float)dy / dx;
    float intery = (float)y1_i + gradient;

    plot(x1_i, y1_i, 1.0f);
    plot(x2_i, y2_i, 1.0f);

    for (int x = x1_i + 1; x < x2_i; x++) {
        plot(x, (int)intery, 1.0f - (intery - (int)intery));
        plot(x, (int)intery + 1, intery - (int)intery);
        intery += gradient;
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
    for (u32 py = y; py < y + h; py++) {
        for (u32 px = x; px < x + w; px++) {
            draw_pixel(px, py, color);
        }
    }
}

void Renderer::draw_char(char c, u32 x, u32 y, u32 color, Font::Style style) {
    Font* font = Font::get_default();

    auto plot_glyph = [&](u32 ox, u32 oy) {
        if (!font || !font->is_valid()) {
            // Minimal fallback: draw a 6x8 block
            if (static_cast<u8>(c) > 32) {
                for (int row = 1; row < 7; row++) {
                    for (int col = 1; col < 6; col++) {
                        draw_pixel(ox + col, oy + row, color);
                    }
                }
            }
            return;
        }

        u32 fw = font->width();
        u32 fh = font->height();

        if (font->is_ttf()) {
            // Antialiased path: blend each pixel by its real coverage
            // value instead of an all-or-nothing bitmap dot.
            const u8* alpha_map = font->get_glyph_alpha(c);
            if (!alpha_map) return;
            for (u32 row = 0; row < fh; row++) {
                for (u32 col = 0; col < fw; col++) {
                    u8 a = alpha_map[row * fw + col];
                    if (a == 0) continue;
                    i32 shear = 0;
                    if (style == Font::Style::Italic) shear = (fh - row) / 4;
                    blend_pixel(ox + col + shear, oy + row, color, a);
                }
            }
            return;
        }

        const u8* glyph = font->get_glyph(c);
        if (!glyph) return;
        u32 bytes_per_line = (fw + 7) / 8;

        for (u32 row = 0; row < fh; row++) {
            for (u32 col = 0; col < fw; col++) {
                u8 byte = glyph[row * bytes_per_line + (col / 8)];
                if ((byte >> (7 - (col % 8))) & 1) {
                    i32 shear = 0;
                    if (style == Font::Style::Italic) shear = (fh - row) / 4;
                    draw_pixel(ox + col + shear, oy + row, color);
                }
            }
        }
    };

    plot_glyph(x, y);
    if (style == Font::Style::Bold) plot_glyph(x + 1, y);
}

void Renderer::draw_text(const char* text, u32 x, u32 y, u32 color, Font::Alignment align, Font::Style style, i32 spacing) {
    if (!text) return;
    Font* font = Font::get_default();
    u32 char_w = (font && font->is_valid()) ? font->width() : 8;
    u32 char_h = (font && font->is_valid()) ? font->height() : 10;
    u32 cur_y = y;

    const char* line_start = text;
    while (*line_start) {
        const char* line_end = line_start;
        u32 line_len = 0;
        while (*line_end && *line_end != '\n') {
            line_len++;
            line_end++;
        }

        u32 total_w = 0;
        for (u32 i = 0; i < line_len; i++) {
            total_w += font ? font->get_char_width(line_start[i]) + spacing : char_w + spacing;
        }
        u32 start_x = x;
        if (align == Font::Alignment::Center) start_x = x - total_w / 2;
        else if (align == Font::Alignment::Right) start_x = x - total_w;

        u32 cur_x = start_x;
        for (u32 i = 0; i < line_len; i++) {
            draw_char(line_start[i], cur_x, cur_y, color, style);
            cur_x += font ? font->get_char_width(line_start[i]) + spacing : char_w + spacing;
        }

        cur_y += char_h;
        line_start = *line_end == '\n' ? line_end + 1 : line_end;
    }
}

void Renderer::measure_text(const char* text, u32& w, u32& h, i32 spacing) {
    Font::measure_string_default(text, w, h, spacing);
}

void Renderer::draw_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    i32 r = (i32)radius;
    for (i32 y = -r; y <= r; y++) {
        for (i32 x = -r; x <= r; x++) {
            float dist = sqrt((float)(x * x + y * y));
            if (dist <= r + 0.5f) {
                float alpha = 1.0f;
                if (dist > r - 0.5f) alpha = 1.0f - (dist - (r - 0.5f));
                if (dist > r - 1.5f) blend_pixel(cx + x, cy + y, color, (u8)(alpha * 255));
            }
        }
    }
}

void Renderer::fill_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    i32 r = (i32)radius;
    u8 color_alpha = (u8)((color >> 24) & 0xFF);
    for (i32 y = -r; y <= r; y++) {
        for (i32 x = -r; x <= r; x++) {
            float dist = sqrt((float)(x * x + y * y));
            if (dist <= r - 0.5f) {
                blend_pixel(cx + x, cy + y, color, color_alpha);
            } else if (dist <= r + 0.5f) {
                float alpha = (1.0f - (dist - (r - 0.5f))) * (color_alpha / 255.0f);
                blend_pixel(cx + x, cy + y, color, (u8)(alpha * 255));
            }
        }
    }
}

void Renderer::draw_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color) {
    draw_line(x + radius, y, x + w - radius, y, color);
    draw_line(x + radius, y + h - 1, x + w - radius, y + h - 1, color);
    draw_line(x, y + radius, x, y + h - radius, color);
    draw_line(x + w - 1, y + radius, x + w - 1, y + h - radius, color);

    auto plot_arc = [&](i32 cx, i32 cy, bool top, bool left) {
        for (i32 dy = - (i32)radius; dy <= 0; dy++) {
            for (i32 dx = - (i32)radius; dx <= 0; dx++) {
                float dist = sqrt((float)(dx * dx + dy * dy));
                if (dist > radius - 1.5f && dist <= radius + 0.5f) {
                    float alpha = 1.0f;
                    if (dist > radius - 0.5f) alpha = 1.0f - (dist - (radius - 0.5f));
                    i32 px = left ? cx + dx : cx - dx;
                    i32 py = top ? cy + dy : cy - dy;
                    blend_pixel(px, py, color, (u8)(alpha * 255));
                }
            }
        }
    };
    plot_arc(x + radius, y + radius, true, true);
    plot_arc(x + w - radius, y + radius, true, false);
    plot_arc(x + radius, y + h - radius, false, true);
    plot_arc(x + w - radius, y + h - radius, false, false);
}

void Renderer::fill_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color) {
    u8 color_alpha = (u8)((color >> 24) & 0xFF);
    blend_rect(x + radius, y, w - 2 * radius, h, color, color_alpha);
    blend_rect(x, y + radius, radius, h - 2 * radius, color, color_alpha);
    blend_rect(x + w - radius, y + radius, radius, h - 2 * radius, color, color_alpha);

    auto fill_corner = [&](u32 cx, u32 cy, u32 r, bool top, bool left) {
        for (i32 dy = -static_cast<i32>(r); dy <= 0; dy++) {
            for (i32 dx = -static_cast<i32>(r); dx <= 0; dx++) {
                float dist = sqrt((float)(dx * dx + dy * dy));
                i32 px = left ? cx + dx : cx - dx;
                i32 py = top ? cy + dy : cy - dy;
                if (dist <= r - 0.5f) {
                    blend_pixel(px, py, color, color_alpha);
                } else if (dist <= r + 0.5f) {
                    float alpha = (1.0f - (dist - (r - 0.5f))) * (color_alpha / 255.0f);
                    blend_pixel(px, py, color, (u8)(alpha * 255));
                }
            }
        }
    };

    fill_corner(x + radius, y + radius, radius, true, true);
    fill_corner(x + w - radius, y + radius, radius, true, false);
    fill_corner(x + radius, y + h - radius, radius, false, true);
    fill_corner(x + w - radius, y + h - radius, radius, false, false);
}

void Renderer::draw_gradient_rect(u32 x, u32 y, u32 w, u32 h, const Gradient& grad) {
    Color start = grad.start;
    Color end = grad.end;
    for (u32 i = 0; i < (grad.horizontal ? w : h); ++i) {
        float t = (float)i / (grad.horizontal ? w : h);
        u8 r = (u8)(start.r + (end.r - start.r) * t);
        u8 g = (u8)(start.g + (end.g - start.g) * t);
        u8 b = (u8)(start.b + (end.b - start.b) * t);
        u8 a = (u8)(start.a + (end.a - start.a) * t);
        u32 color = Color(r, g, b, a).to_argb();
        if (grad.horizontal) blend_rect(x + i, y, 1, h, color, a);
        else blend_rect(x, y + i, w, 1, color, a);
    }
}

void Renderer::draw_border(u32 x, u32 y, u32 w, u32 h, u32 color, u32 thickness) {
    for (u32 i = 0; i < thickness; ++i) {
        draw_rect(x + i, y + i, w - (i * 2), h - (i * 2), color);
    }
}

void Renderer::blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha) {
    for (u32 py = y; py < y + h; py++) {
        for (u32 px = x; px < x + w; px++) {
            blend_pixel(px, py, color, alpha);
        }
    }
}

void Renderer::draw_shadow(u32 x, u32 y, u32 w, u32 h, u32 offset, u8 alpha) {
    // Multi-layered shadow for softness
    blend_rect(x + offset, y + offset, w, h, 0xFF000000, alpha);
    if (offset > 2) {
        blend_rect(x + offset + 2, y + offset + 2, w, h, 0xFF000000, alpha / 2);
    }
}

void Renderer::blit(u32 dx, u32 dy, Surface* src, u32 sx, u32 sy, u32 sw, u32 sh) {
    if (!src || !src->is_valid() || !src->buffer()) return;

    u32 src_w = src->width();
    u32 src_h = src->height();
    u32* src_buf = src->buffer();

    u32 tgt_w = width();
    u32 tgt_h = height();

    if (sw > src_w || sh > src_h) return;

    for (u32 y = 0; y < sh; ++y) {
        u64 sy_coord_64 = static_cast<u64>(sy) + y;
        if (sy_coord_64 >= src_h) break;
        u32 sy_coord = static_cast<u32>(sy_coord_64);

        u64 dy_coord_64 = static_cast<u64>(dy) + y;
        if (dy_coord_64 >= tgt_h) break;
        u32 dy_coord = static_cast<u32>(dy_coord_64);

        for (u32 x = 0; x < sw; ++x) {
            u64 sx_coord_64 = static_cast<u64>(sx) + x;
            if (sx_coord_64 >= src_w) break;
            u32 sx_coord = static_cast<u32>(sx_coord_64);

            u64 dx_coord_64 = static_cast<u64>(dx) + x;
            if (dx_coord_64 >= tgt_w) break;
            u32 dx_coord = static_cast<u32>(dx_coord_64);

            u32 color = src_buf[sy_coord * src_w + sx_coord];
            draw_pixel(dx_coord, dy_coord, color);
        }
    }
}

void Renderer::copy_rect(u32 dx, u32 dy, u32 sx, u32 sy, u32 w, u32 h) {
    u32 tgt_w = width();
    u32 tgt_h = height();

    if (sy == dy) {
        if (sx < dx) {
            // Copy from right to left
            for (u32 y = 0; y < h; ++y) {
                u64 sy_coord_64 = static_cast<u64>(sy) + y;
                if (sy_coord_64 >= tgt_h) continue;
                u32 sy_coord = static_cast<u32>(sy_coord_64);

                u64 dy_coord_64 = static_cast<u64>(dy) + y;
                if (dy_coord_64 >= tgt_h) continue;
                u32 dy_coord = static_cast<u32>(dy_coord_64);

                for (i32 x = (i32)w - 1; x >= 0; --x) {
                    u64 sx_coord_64 = static_cast<u64>(sx) + x;
                    if (sx_coord_64 >= tgt_w) continue;
                    u32 sx_coord = static_cast<u32>(sx_coord_64);

                    u64 dx_coord_64 = static_cast<u64>(dx) + x;
                    if (dx_coord_64 >= tgt_w) continue;
                    u32 dx_coord = static_cast<u32>(dx_coord_64);

                    draw_pixel(dx_coord, dy_coord, get_pixel(sx_coord, sy_coord));
                }
            }
        } else {
            // Copy from left to right
            for (u32 y = 0; y < h; ++y) {
                u64 sy_coord_64 = static_cast<u64>(sy) + y;
                if (sy_coord_64 >= tgt_h) continue;
                u32 sy_coord = static_cast<u32>(sy_coord_64);

                u64 dy_coord_64 = static_cast<u64>(dy) + y;
                if (dy_coord_64 >= tgt_h) continue;
                u32 dy_coord = static_cast<u32>(dy_coord_64);

                for (u32 x = 0; x < w; ++x) {
                    u64 sx_coord_64 = static_cast<u64>(sx) + x;
                    if (sx_coord_64 >= tgt_w) continue;
                    u32 sx_coord = static_cast<u32>(sx_coord_64);

                    u64 dx_coord_64 = static_cast<u64>(dx) + x;
                    if (dx_coord_64 >= tgt_w) continue;
                    u32 dx_coord = static_cast<u32>(dx_coord_64);

                    draw_pixel(dx_coord, dy_coord, get_pixel(sx_coord, sy_coord));
                }
            }
        }
    } else if (sy < dy) {
        // Copy from bottom to top
        for (i32 y = (i32)h - 1; y >= 0; --y) {
            u64 sy_coord_64 = static_cast<u64>(sy) + y;
            if (sy_coord_64 >= tgt_h) continue;
            u32 sy_coord = static_cast<u32>(sy_coord_64);

            u64 dy_coord_64 = static_cast<u64>(dy) + y;
            if (dy_coord_64 >= tgt_h) continue;
            u32 dy_coord = static_cast<u32>(dy_coord_64);

            for (u32 x = 0; x < w; ++x) {
                u64 sx_coord_64 = static_cast<u64>(sx) + x;
                if (sx_coord_64 >= tgt_w) continue;
                u32 sx_coord = static_cast<u32>(sx_coord_64);

                u64 dx_coord_64 = static_cast<u64>(dx) + x;
                if (dx_coord_64 >= tgt_w) continue;
                u32 dx_coord = static_cast<u32>(dx_coord_64);

                draw_pixel(dx_coord, dy_coord, get_pixel(sx_coord, sy_coord));
            }
        }
    } else {
        // Copy from top to bottom
        for (u32 y = 0; y < h; ++y) {
            u64 sy_coord_64 = static_cast<u64>(sy) + y;
            if (sy_coord_64 >= tgt_h) continue;
            u32 sy_coord = static_cast<u32>(sy_coord_64);

            u64 dy_coord_64 = static_cast<u64>(dy) + y;
            if (dy_coord_64 >= tgt_h) continue;
            u32 dy_coord = static_cast<u32>(dy_coord_64);

            for (u32 x = 0; x < w; ++x) {
                u64 sx_coord_64 = static_cast<u64>(sx) + x;
                if (sx_coord_64 >= tgt_w) continue;
                u32 sx_coord = static_cast<u32>(sx_coord_64);

                u64 dx_coord_64 = static_cast<u64>(dx) + x;
                if (dx_coord_64 >= tgt_w) continue;
                u32 dx_coord = static_cast<u32>(dx_coord_64);

                draw_pixel(dx_coord, dy_coord, get_pixel(sx_coord, sy_coord));
            }
        }
    }
}

void Renderer::clear(u32 color) {
    fill_rect(0, 0, width(), height(), color);
}

void Renderer::set_clip_rect(const ClipRect& rect) { m_clip_rect = rect; m_clip_enabled = true; }
void Renderer::clear_clip_rect() { m_clip_enabled = false; }

u32 Renderer::width() const {
    if (m_fb) return m_fb->width();
    if (m_surface) return m_surface->width();
    return 0;
}

u32 Renderer::height() const {
    if (m_fb) return m_fb->height();
    if (m_surface) return m_surface->height();
    return 0;
}

} // namespace acos::graphics
