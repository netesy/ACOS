#pragma once
#include "types.h"

namespace acos::graphics {

inline bool clip_rect_contains(const ClipRect& rect, i32 px, i32 py) {
    return px >= rect.x && px < rect.x + rect.w && py >= rect.y && py < rect.y + rect.h;
}

inline bool clip_rect_intersects(const ClipRect& r1, const ClipRect& r2) {
    return r1.x < r2.x + r2.w && r1.x + r1.w > r2.x &&
           r1.y < r2.y + r2.h && r1.y + r1.h > r2.y;
}

inline ClipRect clip_rect_intersect(const ClipRect& r1, const ClipRect& r2) {
    i32 nx = r1.x > r2.x ? r1.x : r2.x;
    i32 ny = r1.y > r2.y ? r1.y : r2.y;
    i32 nw = (r1.x + r1.w < r2.x + r2.w ? r1.x + r1.w : r2.x + r2.w) - nx;
    i32 nh = (r1.y + r1.h < r2.y + r2.h ? r1.y + r1.h : r2.y + r2.h) - ny;
    if (nw < 0) nw = 0;
    if (nh < 0) nh = 0;
    return ClipRect{nx, ny, nw, nh};
}

} // namespace acos::graphics
