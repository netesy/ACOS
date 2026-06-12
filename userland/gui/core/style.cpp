#include <acos/process.h>
#include <acos/runtime.h>
#include "style.h"
#include "../theme.h"

namespace acos::gui {

Style::Style() : background_color(0),
                 foreground_color(widgets::g_current_theme.text),
                 border_color(widgets::g_current_theme.border),
                 border_width(0),
                 border_radius(widgets::g_current_theme.widget_radius),
                 padding_left(0), padding_right(0), padding_top(0), padding_bottom(0),
                 margin_left(0), margin_right(0), margin_top(0), margin_bottom(0),
                 preferred_w(0), preferred_h(0),
                 flex_grow(0),
                 position(Position::Static),
                 anchor_top(-1), anchor_right(-1), anchor_bottom(-1), anchor_left(-1),
                 elevation(0), opacity(1.0f) {
}

} // namespace acos::gui
