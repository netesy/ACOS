#pragma once
#include "framebuffer.h"
#include "font.h"
#include "types.h"
#include "surface.h"

namespace acos::graphics {

class Renderer {
public:
    Renderer(Framebuffer* fb, Surface* surface = nullptr);

    // Basic drawing
    void draw_pixel(u32 x, u32 y, u32 color);
    u32 get_pixel(u32 x, u32 y) const;
    void draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
    void draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);

    // Text drawing
    void draw_char(char c, u32 x, u32 y, u32 color, Font::Style style = Font::Style::Regular);
    void draw_text(const char* text, u32 x, u32 y, u32 color,
                   Font::Alignment align = Font::Alignment::Left,
                   Font::Style style = Font::Style::Regular,
                   i32 spacing = 0);
    void measure_text(const char* text, u32& w, u32& h, i32 spacing = 0);
    
    // Advanced drawing
    void draw_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void fill_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void draw_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color);
    void fill_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 color);
    void draw_gradient_rect(u32 x, u32 y, u32 w, u32 h, const Gradient& grad);
    void draw_border(u32 x, u32 y, u32 w, u32 h, u32 color, u32 thickness);
    
    // Blending and effects
    void blend_pixel(u32 x, u32 y, u32 color, u8 alpha);
    void blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha);
    void draw_shadow(u32 x, u32 y, u32 w, u32 h, u32 offset, u8 alpha);
    
    // Blit and copy operations
    void blit(u32 dx, u32 dy, Surface* src, u32 sx, u32 sy, u32 sw, u32 sh);
    void copy_rect(u32 dx, u32 dy, u32 sx, u32 sy, u32 w, u32 h);
    void clear(u32 color);

    // Clipping
    void set_clip_rect(const ClipRect& rect);
    void clear_clip_rect();

    // Dimensions
    u32 width() const;
    u32 height() const;

private:
    Framebuffer* m_fb;
    Surface* m_surface;
    ClipRect m_clip_rect;
    bool m_clip_enabled;

    bool is_clipped(u32 x, u32 y) const {
        if (x >= width() || y >= height()) return true;
        if (!m_clip_enabled) return false;
        return x < (u32)m_clip_rect.x || x >= (u32)(m_clip_rect.x + m_clip_rect.w) ||
               y < (u32)m_clip_rect.y || y >= (u32)(m_clip_rect.y + m_clip_rect.h);
    }
};

} // namespace acos::graphics
