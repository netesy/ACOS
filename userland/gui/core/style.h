#pragma once
#include <acos/types.h>

namespace acos::gui {

struct Style {
    ::acos::u32 background_color;
    ::acos::u32 foreground_color;
    ::acos::u32 border_color;
    ::acos::u32 border_radius;

    ::acos::u32 padding_left;
    ::acos::u32 padding_right;
    ::acos::u32 padding_top;
    ::acos::u32 padding_bottom;

    ::acos::u32 elevation;
    float opacity;

    Style();
};

} // namespace acos::gui
