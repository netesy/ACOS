#include "style.h"
#include "../theme.h"

namespace acos::gui {

Style::Style() {
    background_color = g_current_theme.surface;
    foreground_color = g_current_theme.text;
    border_color = g_current_theme.border;
    border_width = g_current_theme.border_width;
    border_radius = g_current_theme.widget_radius;
    padding_left = padding_right = padding_top = padding_bottom = 0;
    margin_left = margin_right = margin_top = margin_bottom = 0;
    elevation = 0;
    opacity = 1.0f;
}

} // namespace acos::gui
