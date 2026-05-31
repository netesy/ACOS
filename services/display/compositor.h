#pragma once
#include <acos/types.h>
#include <kernel/graphics/framebuffer.h>
#include "window.h"
#include "surface_manager.h"

namespace acos::display {

class Compositor {
public:
    Compositor(acos::graphics::Framebuffer* fb, SurfaceManager* surface_manager);

    void compose();
    void mark_dirty(u32 x, u32 y, u32 w, u32 h);

    void set_windows(Window** windows, usize count);

private:
    acos::graphics::Framebuffer* m_fb;
    SurfaceManager* m_surface_manager;

    Window** m_windows;
    usize m_window_count;

    // Simple damage tracking
    u32 m_dirty_x, m_dirty_y, m_dirty_w, m_dirty_h;
    bool m_has_damage;
};

} // namespace acos::display
