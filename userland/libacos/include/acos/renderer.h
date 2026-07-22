#pragma once
#include <acos/types.h>
#include <acos/framebuffer.h>
#include <acos/graphics_types.h>

namespace acos::graphics {

class Renderer {
public:
    Renderer(Framebuffer* fb);

    void draw_pixel(u32 x, u32 y, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void blend_pixel(u32 x, u32 y, u32 color, u8 alpha);

    void draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void draw_line(u32 x0, u32 y0, u32 x1, u32 y1, u32 color);
    void draw_circle(u32 xc, u32 yc, u32 r, u32 color);
    void fill_circle(u32 xc, u32 yc, u32 r, u32 color);
    void blend_rect(u32 x, u32 y, u32 w, u32 h, u32 color, u8 alpha);

    void draw_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 r, u32 color);
    void fill_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 r, u32 color);

    void blend_circle(u32 xc, u32 yc, u32 r, u32 color, u8 alpha);

    // Frosted-glass panel: box-blurs whatever has already been drawn behind
    // (x,y,w,h) and then blends `tint` over it at `alpha`, clipped to a
    // rounded-rect shape of the given corner radius.
    void blend_glass_rounded_rect(u32 x, u32 y, u32 w, u32 h, u32 radius, u32 tint, u8 alpha, u32 blur_step = 3);

    // Draws an RGBA8888 bitmap (src_w x src_h) scaled into the destination
    // rect (x,y,w,h), alpha-compositing each pixel onto the framebuffer.
    void draw_bitmap(u32 x, u32 y, u32 w, u32 h, const unsigned char* rgba, u32 src_w, u32 src_h);

    void draw_text(const char* text, u32 x, u32 y, u32 color);
    void measure_text(const char* text, u32& w, u32& h);

    void draw_shadow(u32 x, u32 y, u32 w, u32 h, u32 offset, u8 alpha);

    u32 width() const { return m_fb ? m_fb->width() : 0; }
    u32 height() const { return m_fb ? m_fb->height() : 0; }

private:
    Framebuffer* m_fb;
};

} // namespace acos::graphics
