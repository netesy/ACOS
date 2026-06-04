#pragma once
#include <acos/types.h>

namespace acos::gui {

struct Size {
    i32 w, h;

    bool operator==(const Size& other) const {
        return w == other.w && h == other.h;
    }
};

struct BoxConstraints {
    i32 min_w, max_w;
    i32 min_h, max_h;

    static constexpr i32 Infinity = 0x3FFFFFFF;

    static BoxConstraints loose(i32 max_w, i32 max_h) {
        return {0, max_w, 0, max_h};
    }

    static BoxConstraints tight(i32 w, i32 h) {
        return {w, w, h, h};
    }

    Size constrain(Size size) const {
        i32 w = size.w;
        if (w < min_w) w = min_w;
        if (w > max_w) w = max_w;
        i32 h = size.h;
        if (h < min_h) h = min_h;
        if (h > max_h) h = max_h;
        return {w, h};
    }

    bool is_tight_w() const { return min_w >= max_w; }
    bool is_tight_h() const { return min_h >= max_h; }
};

} // namespace acos::gui
