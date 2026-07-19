#pragma once
#include <acos/types.h>
#include "clipping.h"
#include "surface.h"
#include "display.h"
#include "renderer.h"

namespace acos::graphics {

class GraphicsContext {
public:
    enum class TargetType {
        Display,
        Surface
    };

    GraphicsContext(TargetType type, u64 target_handle);
    ~GraphicsContext() = default;

    TargetType target_type() const { return m_target_type; }
    u64 target_handle() const { return m_target_handle; }

    void put_pixel(u32 x, u32 y, u32 color);
    void draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
    void draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void draw_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void fill_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void blit(u32 dx, u32 dy, Surface* src_surface, u32 sx, u32 sy, u32 sw, u32 sh);
    void clear(u32 color);
    void copy_rect(u32 dx, u32 dy, u32 sx, u32 sy, u32 w, u32 h);

    void set_clip_rect(const ClipRect& rect);
    void clear_clip_rect();

    u32 width() const;
    u32 height() const;

private:
    TargetType m_target_type;
    u64 m_target_handle;
    ClipRect m_clip_rect;
    bool m_clip_enabled;
};

} // namespace acos::graphics
