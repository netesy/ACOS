#include <kernel/graphics/framebuffer.h>

namespace acos::graphics {

Framebuffer::Framebuffer(u64 base, u64 size, u32 width, u32 height, u32 pitch, u32 bpp, PixelFormat format)
    : m_base(base), m_size(size), m_width(width), m_height(height), m_pitch(pitch), m_bpp(bpp), m_format(format), m_clipping_enabled(false) {
    m_clip_rect.x = 0;
    m_clip_rect.y = 0;
    m_clip_rect.w = width;
    m_clip_rect.h = height;
}

void Framebuffer::put_pixel(u32 x, u32 y, u32 color) {
    if (x >= m_width || y >= m_height) return;
    if (m_clipping_enabled && is_clipped(x, y)) return;

    u8 r = (color >> 16) & 0xFF;
    u8 g = (color >> 8) & 0xFF;
    u8 b = color & 0xFF;

    u32 final_color = color;
    if (m_format == PixelFormat::BGR) {
        final_color = (b << 16) | (g << 8) | r;
    }

    u8* fb = reinterpret_cast<u8*>(m_base);
    if (m_bpp == 32) {
        u32 offset = y * m_pitch * 4 + x * 4;
        if (offset + 4 <= m_size) {
            *reinterpret_cast<u32*>(fb + offset) = final_color;
        }
    } else if (m_bpp == 24) {
        u32 offset = y * m_pitch * 3 + x * 3;
        if (offset + 3 <= m_size) {
            fb[offset] = b;
            fb[offset + 1] = g;
            fb[offset + 2] = r;
        }
    }
}

u32 Framebuffer::get_pixel(u32 x, u32 y) const {
    if (x >= m_width || y >= m_height) return 0;
    const u8* fb = reinterpret_cast<const u8*>(m_base);

    if (m_bpp == 32) {
        u32 offset = y * m_pitch * 4 + x * 4;
        if (offset + 4 <= m_size) {
            u32 color = *reinterpret_cast<const u32*>(fb + offset);
            if (m_format == PixelFormat::BGR) {
                u8 b = (color >> 16) & 0xFF;
                u8 g = (color >> 8) & 0xFF;
                u8 r = color & 0xFF;
                return (r << 16) | (g << 8) | b;
            }
            return color;
        }
    } else if (m_bpp == 24) {
        u32 offset = y * m_pitch * 3 + x * 3;
        if (offset + 3 <= m_size) {
            u8 b = fb[offset];
            u8 g = fb[offset + 1];
            u8 r = fb[offset + 2];
            return (r << 16) | (g << 8) | b;
        }
    }
    return 0;
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

void Framebuffer::draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    int dx = static_cast<int>(x2) - static_cast<int>(x1);
    int dy = static_cast<int>(y2) - static_cast<int>(y1);
    int abs_dx = dx < 0 ? -dx : dx;
    int abs_dy = dy < 0 ? -dy : dy;
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = abs_dx - abs_dy;

    u32 curr_x = x1;
    u32 curr_y = y1;

    while (true) {
        put_pixel(curr_x, curr_y, color);
        if (curr_x == x2 && curr_y == y2) break;
        int e2 = 2 * err;
        if (e2 > -abs_dy) {
            err -= abs_dy;
            curr_x += sx;
        }
        if (e2 < abs_dx) {
            err += abs_dx;
            curr_y += sy;
        }
    }
}

void Framebuffer::draw_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    int x = static_cast<int>(radius);
    int y = 0;
    int err = 0;

    while (x >= y) {
        put_pixel(cx + x, cy + y, color);
        put_pixel(cx + y, cy + x, color);
        put_pixel(cx - y, cy + x, color);
        put_pixel(cx - x, cy + y, color);
        put_pixel(cx - x, cy - y, color);
        put_pixel(cx - y, cy - x, color);
        put_pixel(cx + y, cy - x, color);
        put_pixel(cx + x, cy - x, color);

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x -= 1;
            err += 2 * (y - x) + 1;
        }
    }
}

void Framebuffer::fill_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    int x = static_cast<int>(radius);
    int y = 0;
    int err = 0;

    while (x >= y) {
        draw_line(cx - x, cy + y, cx + x, cy + y, color);
        draw_line(cx - y, cy + x, cx + y, cy + x, color);
        draw_line(cx - x, cy - y, cx + x, cy - y, color);
        draw_line(cx - y, cy - x, cx + y, cy - x, color);

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x -= 1;
            err += 2 * (y - x) + 1;
        }
    }
}

void Framebuffer::draw_gradient_rect(u32 x, u32 y, u32 w, u32 h, const Gradient& grad) {
    u32 start_argb = grad.start.to_argb();
    u32 end_argb = grad.end.to_argb();

    u8 r1 = (start_argb >> 16) & 0xFF;
    u8 g1 = (start_argb >> 8) & 0xFF;
    u8 b1 = start_argb & 0xFF;

    u8 r2 = (end_argb >> 16) & 0xFF;
    u8 g2 = (end_argb >> 8) & 0xFF;
    u8 b2 = end_argb & 0xFF;

    for (u32 i = y; i < y + h && i < m_height; ++i) {
        float ratio = static_cast<float>(i - y) / static_cast<float>(h);
        if (grad.horizontal) {
            for (u32 j = x; j < x + w && j < m_width; ++j) {
                float h_ratio = static_cast<float>(j - x) / static_cast<float>(w);
                u8 r = r1 + static_cast<u8>((r2 - r1) * h_ratio);
                u8 g = g1 + static_cast<u8>((g2 - g1) * h_ratio);
                u8 b = b1 + static_cast<u8>((b2 - b1) * h_ratio);
                put_pixel(j, i, (r << 16) | (g << 8) | b);
            }
        } else {
            u8 r = r1 + static_cast<u8>((r2 - r1) * ratio);
            u8 g = g1 + static_cast<u8>((g2 - g1) * ratio);
            u8 b = b1 + static_cast<u8>((b2 - b1) * ratio);
            u32 color = (r << 16) | (g << 8) | b;
            for (u32 j = x; j < x + w && j < m_width; ++j) {
                put_pixel(j, i, color);
            }
        }
    }
}

void Framebuffer::draw_border(u32 x, u32 y, u32 w, u32 h, u32 color, u32 thickness) {
    fill_rect(x, y, w, thickness, color); // Top
    fill_rect(x, y + h - thickness, w, thickness, color); // Bottom
    fill_rect(x, y, thickness, h, color); // Left
    fill_rect(x + w - thickness, y, thickness, h, color); // Right
}

void Framebuffer::blend_pixel(u32 x, u32 y, u32 color, u8 alpha) {
    if (alpha == 255) {
        put_pixel(x, y, color);
        return;
    }
    if (alpha == 0) return;

    u32 bg = get_pixel(x, y);

    u8 r_fg = (color >> 16) & 0xFF;
    u8 g_fg = (color >> 8) & 0xFF;
    u8 b_fg = color & 0xFF;

    u8 r_bg = (bg >> 16) & 0xFF;
    u8 g_bg = (bg >> 8) & 0xFF;
    u8 b_bg = bg & 0xFF;

    u8 r = ((r_fg * alpha) + (r_bg * (255 - alpha))) / 255;
    u8 g = ((g_fg * alpha) + (g_bg * (255 - alpha))) / 255;
    u8 b = ((b_fg * alpha) + (b_bg * (255 - alpha))) / 255;

    put_pixel(x, y, (r << 16) | (g << 8) | b);
}

void Framebuffer::blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha) {
    for (u32 i = y; i < y + h && i < m_height; ++i) {
        for (u32 j = x; j < x + w && j < m_width; ++j) {
            blend_pixel(j, i, color, alpha);
        }
    }
}

void Framebuffer::set_clip_rect(const ClipRect& rect) {
    m_clip_rect = rect;
    m_clipping_enabled = true;
}

void Framebuffer::clear_clip_rect() {
    m_clipping_enabled = false;
}

bool Framebuffer::is_clipped(u32 x, u32 y) const {
    if (!m_clipping_enabled) return false;
    return (x < static_cast<u32>(m_clip_rect.x) || x >= static_cast<u32>(m_clip_rect.x + m_clip_rect.w) ||
            y < static_cast<u32>(m_clip_rect.y) || y >= static_cast<u32>(m_clip_rect.y + m_clip_rect.h));
}

} // namespace acos::graphics
