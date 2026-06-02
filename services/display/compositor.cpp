#include "compositor.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::display {

Compositor::Compositor(acos::graphics::Framebuffer* fb, SurfaceManager* surface_manager)
    : m_fb(fb), m_surface_manager(surface_manager), m_windows(nullptr), m_window_count(0),
      m_dirty_x(0), m_dirty_y(0), m_dirty_w(0), m_dirty_h(0), m_has_damage(true) {}

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
    if (!m_has_damage) return;

    // Nothing to composite yet — preserve whatever is on the framebuffer
    // (e.g. the desktop shell's initial render) instead of clearing it.
    if (m_window_count == 0) {
        m_has_damage = false;
        return;
    }

    u32 background_color = 0x001E3A5F;
    m_fb->clear(background_color);

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
                if (color != 0) {
                    m_fb->put_pixel(win_x + x, win_y + y, color);
                }
            }
        }
    }

    m_has_damage = false;
}

} // namespace acos::display
