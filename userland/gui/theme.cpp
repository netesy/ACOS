#include "theme.h"

namespace acos::gui {

Theme g_current_theme;

void init_default_theme() {
    g_current_theme.background = 0x001E3A5F; // ACOS Blue
    g_current_theme.foreground = 0xFFFFFFFF; // White
    g_current_theme.accent = 0x004A90E2;     // Lighter Blue
    g_current_theme.border = 0xFFCCCCCC;     // Gray
    g_current_theme.text = 0xFFFFFFFF;       // White
    g_current_theme.widget_bg = 0xCC333333;  // Dark Transparent Gray
}

} // namespace acos::gui
