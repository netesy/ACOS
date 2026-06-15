#pragma once
#include <acos/types.h>
#include <kernel/graphics/types.h>

namespace acos::graphics {

class Framebuffer {
public:
    Framebuffer(u64 base, u64 size, u32 width, u32 height, u32 pitch, u32 bpp);

    // Basic operations
    void put_pixel(u32 x, u32 y, u32 color);
    u32 get_pixel(u32 x, u32 y) const;
    void clear(u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    
    // Advanced operations
    void draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
    void draw_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void fill_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void draw_gradient_rect(u32 x, u32 y, u32 w, u32 h, const Gradient& grad);
    void draw_border(u32 x, u32 y, u32 w, u32 h, u32 color, u32 thickness);
    
    // Blending
    void blend_pixel(u32 x, u32 y, u32 color, u8 alpha);
    void blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha);
    
    // Clipping
    void set_clip_rect(const ClipRect& rect);
    void clear_clip_rect();
    bool is_clipped(u32 x, u32 y) const;

    u32 width() const { return m_width; }
    u32 height() const { return m_height; }
    u64 base() const { return m_base; }
    u64 size() const { return m_size; }
    u32 pitch() const { return m_pitch; }

private:
    u64 m_base;
    u64 m_size;
    u32 m_width;
    u32 m_height;
    u32 m_pitch;
    u32 m_bpp;
    ClipRect m_clip_rect;
    bool m_clipping_enabled;
};

} // namespace acos::graphics
