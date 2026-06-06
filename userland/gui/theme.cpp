#include "theme.h"

namespace acos::gui::widgets {

Theme g_current_theme;

void init_synthetic_theme() {
    g_current_theme.background = 0xFF0A0A0B;
    g_current_theme.surface = 0xFF131314;
    g_current_theme.glass_bg = 0x99131314;
    g_current_theme.primary = 0xFF00E5FF;
    g_current_theme.secondary = 0xFFBF00FF;
    g_current_theme.border = 0xFF444444;
    g_current_theme.text = 0xFFE5E2E3;
    g_current_theme.foreground = 0xFFE5E2E3;
    g_current_theme.text_secondary = 0xFF888888;
    g_current_theme.accent = 0xFF00E5FF;
    g_current_theme.info = 0xFF00E5FF;
    g_current_theme.success = 0xFF00C853;
    g_current_theme.warning = 0xFFFFD600;
    g_current_theme.error = 0xFFFF1744;
    g_current_theme.widget_bg = 0x33FFFFFF;
    g_current_theme.widget_bg_hover = 0x44FFFFFF;
    g_current_theme.widget_bg_pressed = 0x55FFFFFF;
    g_current_theme.shadow = 0xFF000000;
    g_current_theme.shadow_alpha = 128;
    g_current_theme.window_radius = 16;
    g_current_theme.widget_radius = 8;
    g_current_theme.border_width = 1;
}

void init_default_theme() { init_synthetic_theme(); }
void init_dark_theme() { init_synthetic_theme(); }
void init_light_theme() { init_synthetic_theme(); }

} // namespace acos::gui::widgets
