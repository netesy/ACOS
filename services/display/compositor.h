#pragma once
#include <acos/types.h>
#include <kernel/graphics/framebuffer.h>
#include <kernel/graphics/renderer.h>
#include "window.h"
#include "surface_manager.h"

namespace acos::display {

class Compositor {
public:
    Compositor(acos::graphics::Framebuffer* fb, SurfaceManager* surface_manager);

    void compose();
    void mark_dirty(u32 x, u32 y, u32 w, u32 h);
    void mark_always_dirty() { m_always_dirty = true; }

    void set_windows(Window** windows, usize count);

    // Desktop background draw callback
    typedef void (*DesktopDrawFn)(acos::graphics::Renderer*);
    void set_desktop_draw(DesktopDrawFn fn) { m_desktop_draw = fn; }

    acos::graphics::Renderer* renderer() { return &m_renderer; }

private:
    acos::graphics::Framebuffer* m_fb;
    SurfaceManager* m_surface_manager;
    acos::graphics::Renderer m_renderer;

    Window** m_windows;
    usize m_window_count;

    // Desktop background draw function
    DesktopDrawFn m_desktop_draw;

    // Simple damage tracking
    u32 m_dirty_x, m_dirty_y, m_dirty_w, m_dirty_h;
    bool m_has_damage;
    bool m_always_dirty;
};

} // namespace acos::display
