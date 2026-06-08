#pragma once
#include <acos/types.h>

namespace acos::gui {

enum class Position {
    Static,    // normal flow (default)
    Relative,  // offset from normal position
    Absolute,  // positioned relative to nearest non-static ancestor
    Fixed,     // positioned relative to screen/viewport
};

struct Style {
    ::acos::u32 background_color;
    ::acos::u32 foreground_color;
    ::acos::u32 border_color;
    ::acos::u32 border_width;
    ::acos::u32 border_radius;

    // Padding (inner spacing)
    ::acos::u32 padding_left;
    ::acos::u32 padding_right;
    ::acos::u32 padding_top;
    ::acos::u32 padding_bottom;

    // Margin (outer spacing between siblings)
    ::acos::u32 margin_left;
    ::acos::u32 margin_right;
    ::acos::u32 margin_top;
    ::acos::u32 margin_bottom;

    // Preferred / intrinsic size (0 = fill/auto)
    ::acos::i32 preferred_w;
    ::acos::i32 preferred_h;

    // Flex grow factor (0 = fixed, 1+ = grow proportionally)
    ::acos::u32 flex_grow;

    // Positioning
    Position position;
    // Anchor offsets — used for Absolute/Fixed/Relative
    // Use -1 to mean "not set" (unanchored on that edge)
    ::acos::i32 anchor_top;
    ::acos::i32 anchor_right;
    ::acos::i32 anchor_bottom;
    ::acos::i32 anchor_left;

    ::acos::u32 elevation;
    float opacity;

    Style();
};

} // namespace acos::gui
