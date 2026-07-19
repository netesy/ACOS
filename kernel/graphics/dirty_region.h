#pragma once
#include "clipping.h"

namespace acos::graphics {

class DirtyRegion {
public:
    constexpr DirtyRegion() : m_rect{0, 0, 0, 0}, m_empty(true) {}

    void invalidate(i32 x, i32 y, i32 w, i32 h) {
        if (w <= 0 || h <= 0) return;
        if (m_empty) {
            m_rect = ClipRect{x, y, w, h};
            m_empty = false;
        } else {
            i32 x1 = m_rect.x;
            i32 y1 = m_rect.y;
            i32 x2 = m_rect.x + m_rect.w;
            i32 y2 = m_rect.y + m_rect.h;

            i32 nx1 = x < x1 ? x : x1;
            i32 ny1 = y < y1 ? y : y1;
            i32 nx2 = x + w > x2 ? x + w : x2;
            i32 ny2 = y + h > y2 ? y + h : y2;

            m_rect = ClipRect{nx1, ny1, nx2 - nx1, ny2 - ny1};
        }
    }

    void reset() {
        m_rect = ClipRect{0, 0, 0, 0};
        m_empty = true;
    }

    const ClipRect& rect() const { return m_rect; }
    bool is_empty() const { return m_empty; }

private:
    ClipRect m_rect;
    bool m_empty;
};

} // namespace acos::graphics
