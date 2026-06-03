#pragma once
#include <acos/types.h>

namespace acos::ui {

struct Size {
    i32 w, h;
};

struct Position {
    i32 x, y;
};

struct Constraints {
    i32 min_w, max_w;
    i32 min_h, max_h;

    static Constraints loose(i32 max_w, i32 max_h) {
        return { 0, max_w, 0, max_h };
    }

    static Constraints tight(i32 w, i32 h) {
        return { w, w, h, h };
    }
};

} // namespace acos::ui
