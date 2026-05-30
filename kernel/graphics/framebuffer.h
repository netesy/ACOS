#pragma once
#include <acos/types.h>

namespace acos::graphics {

class Framebuffer {
public:
    Framebuffer(u64 base, u64 size, u32 width, u32 height, u32 pitch, u32 bpp);

    void put_pixel(u32 x, u32 y, u32 color);
    u32 get_pixel(u32 x, u32 y) const;
    void clear(u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);

    u32 width() const { return m_width; }
    u32 height() const { return m_height; }
    u64 base() const { return m_base; }

private:
    u64 m_base;
    u64 m_size;
    u32 m_width;
    u32 m_height;
    u32 m_pitch;
    u32 m_bpp;
};

} // namespace acos::graphics
