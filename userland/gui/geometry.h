#pragma once
#include <acos/types.h>

namespace acos::ui {

struct Size {
    i32 w, h;
    static Size zero() { return {0, 0}; }
};

struct Position {
    i32 x, y;
    static Position zero() { return {0, 0}; }
};

struct Constraints {
    i32 min_w, max_w, min_h, max_h;
    static Constraints loose(i32 max_w, i32 max_h) { return { 0, max_w, 0, max_h }; }
    static Constraints tight(i32 w, i32 h) { return { w, w, h, h }; }

    Size satisfy(Size size) const {
        i32 w = size.w; if (w < min_w) w = min_w; if (w > max_w) w = max_w;
        i32 h = size.h; if (h < min_h) h = min_h; if (h > max_h) h = max_h;
        return { w, h };
    }
};

} // namespace acos::ui
