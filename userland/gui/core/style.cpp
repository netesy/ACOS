#include "style.h"
#include "../theme.h"

namespace acos::gui {

Style::Style() : background_color(0),
                 foreground_color(widgets::g_current_theme.text),
                 border_color(widgets::g_current_theme.border),
                 border_radius(widgets::g_current_theme.widget_radius),
                 padding_left(0), padding_right(0), padding_top(0), padding_bottom(0),
                 elevation(0), opacity(1.0f) {
}

} // namespace acos::gui
