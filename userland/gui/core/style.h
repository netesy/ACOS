#pragma once
#include <acos/types.h>

namespace acos::gui {

struct Style {
    u32 background_color;
    u32 foreground_color;
    u32 border_color;
    u32 border_width;
    u32 border_radius;
    u32 padding_left, padding_right, padding_top, padding_bottom;
    u32 margin_left, margin_right, margin_top, margin_bottom;
    u32 elevation;

    Style();
};

} // namespace acos::gui
