#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/graphics.h>
#include <services/display/compositor.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::display {

namespace {
constexpr u32 kCursorW = 12;
constexpr u32 kCursorH = 19;
}

Compositor::Compositor(acos::graphics::Framebuffer* fb, SurfaceManager* surface_manager)
    : m_fb(fb), m_surface_manager(surface_manager), m_renderer(fb),
      m_windows(nullptr), m_window_count(0), m_desktop_draw(nullptr),
      m_dirty_x(0), m_dirty_y(0), m_dirty_w(0), m_dirty_h(0),
      m_has_damage(true), m_always_dirty(false),
      m_cursor_x(kDefaultCursorX), m_cursor_y(kDefaultCursorY), m_cursor_visible(true) {}

void Compositor::set_cursor_position(u32 x, u32 y) {
    if (x == m_cursor_x && y == m_cursor_y) return;

    // Damage both the old and new cursor footprint so compose() actually
    // redraws this frame even if nothing else on screen changed.
    mark_dirty(m_cursor_x, m_cursor_y, kCursorW, kCursorH);
    mark_dirty(x, y, kCursorW, kCursorH);

    m_cursor_x = x;
    m_cursor_y = y;
}

void Compositor::set_cursor_visible(bool visible) {
    if (visible == m_cursor_visible) return;
    m_cursor_visible = visible;
    mark_dirty(m_cursor_x, m_cursor_y, kCursorW, kCursorH);
}

// Simple 12x19 arrow-pointer sprite, rasterized scanline-by-scanline.
// row_widths[i] is how many pixels wide the (left-aligned) filled part of
// the arrow silhouette is on row i; this approximates the classic OS arrow
// cursor without needing a bitmap asset.
void Compositor::draw_cursor() {
    if (!m_cursor_visible) return;

    static constexpr u32 row_widths[kCursorH] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 6, 5, 5, 2, 2, 0, 0, 0
    };

    // 1px black outline first (drawn slightly larger/offset), then a white
    // fill on top, so the pointer stays visible against any background.
    for (u32 row = 0; row < kCursorH; row++) {
        u32 w = row_widths[row];
        if (w == 0) continue;
        i32 oy = (i32)m_cursor_y + (i32)row - 1;
        if (oy < 0) continue;
        u32 ox = (m_cursor_x > 0) ? m_cursor_x - 1 : 0;
        u32 ow = (m_cursor_x > 0) ? w + 2 : w + 1;
        m_renderer.fill_rect(ox, (u32)oy, ow, 1, 0xFF000000);
    }
    for (u32 row = 0; row < kCursorH; row++) {
        u32 w = row_widths[row];
        if (w == 0) continue;
        m_renderer.fill_rect(m_cursor_x, m_cursor_y + row, w, 1, 0xFFFFFFFF);
    }
}

void Compositor::set_windows(Window** windows, usize count) {
    m_windows = windows;
    m_window_count = count;
}

void Compositor::mark_dirty(u32 x, u32 y, u32 w, u32 h) {
    if (!m_has_damage) {
        m_dirty_x = x;
        m_dirty_y = y;
        m_dirty_w = w;
        m_dirty_h = h;
        m_has_damage = true;
    } else {
        u32 x2 = x + w;
        u32 y2 = y + h;
        u32 dx2 = m_dirty_x + m_dirty_w;
        u32 dy2 = m_dirty_y + m_dirty_h;

        m_dirty_x = (x < m_dirty_x) ? x : m_dirty_x;
        m_dirty_y = (y < m_dirty_y) ? y : m_dirty_y;

        u32 nx2 = (x2 > dx2) ? x2 : dx2;
        u32 ny2 = (y2 > dy2) ? y2 : dy2;

        m_dirty_w = nx2 - m_dirty_x;
        m_dirty_h = ny2 - m_dirty_y;
    }
}

void Compositor::compose() {
    if (!m_has_damage && !m_always_dirty) return;

    // Draw desktop background first
    if (m_desktop_draw) {
        m_desktop_draw(&m_renderer);
    } else {
        // Default: Asade Synthetic background
        m_fb->clear(0xFF0A0A0B);
    }

    u32 fb_width = m_fb->width();
    u32 fb_height = m_fb->height();

    for (usize i = 0; i < m_window_count; i++) {
        Window* win = m_windows[i];
        if (!win || !win->is_visible()) continue;

        Surface* surface = m_surface_manager->get_surface(win->surface_id());
        if (!surface) continue;

        u32 win_x = win->x();
        u32 win_y = win->y();
        u32 win_w = win->width();
        u32 win_h = win->height();

        for (u32 y = 0; y < win_h; y++) {
            if (win_y + y >= fb_height) break;
            for (u32 x = 0; x < win_w; x++) {
                if (win_x + x >= fb_width) break;

                u32 color = surface->buffer[y * win_w + x];
                u8 alpha = (color >> 24) & 0xFF;

                if (alpha == 255) {
                    m_fb->put_pixel(win_x + x, win_y + y, color);
                } else if (alpha > 0) {
                    // Alpha blend with what's already in the framebuffer
                    u32 bg = m_fb->get_pixel(win_x + x, win_y + y);

                    u32 rb = (color & 0xFF00FF) * alpha + (bg & 0xFF00FF) * (255 - alpha);
                    u32 g = (color & 0x00FF00) * alpha + (bg & 0x00FF00) * (255 - alpha);

                    u32 blended = ((rb >> 8) & 0xFF00FF) | ((g >> 8) & 0x00FF00);
                    m_fb->put_pixel(win_x + x, win_y + y, 0xFF000000 | blended);
                }
            }
        }
    }

    draw_cursor();

    m_has_damage = false;
}

} // namespace acos::display
