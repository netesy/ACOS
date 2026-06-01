#include "theme.h"

namespace acos::gui {

Theme g_current_theme;

void init_default_theme() {
    // ACOS Blue theme
    g_current_theme.background = 0xFF001E3A;
    g_current_theme.foreground = 0xFFFFFFFF;
    g_current_theme.accent = 0xFF004A90;
    g_current_theme.accent_light = 0xFF0066CC;
    g_current_theme.accent_dark = 0xFF003366;
    
    g_current_theme.border = 0xFFCCCCCC;
    g_current_theme.text = 0xFFFFFFFF;
    g_current_theme.text_secondary = 0xFF999999;
    g_current_theme.widget_bg = 0xCC333333;
    g_current_theme.widget_bg_hover = 0xCC444444;
    g_current_theme.widget_bg_pressed = 0xCC222222;
    
    g_current_theme.success = 0xFF00CC00;
    g_current_theme.warning = 0xFFFFCC00;
    g_current_theme.error = 0xFFCC0000;
    g_current_theme.info = 0xFF0099FF;
    
    g_current_theme.shadow = 0xFF000000;
    g_current_theme.shadow_alpha = 128;
}

void init_dark_theme() {
    g_current_theme.background = 0xFF1A1A1A;
    g_current_theme.foreground = 0xFFE0E0E0;
    g_current_theme.accent = 0xFF0066FF;
    g_current_theme.accent_light = 0xFF3399FF;
    g_current_theme.accent_dark = 0xFF0033CC;
    
    g_current_theme.border = 0xFF444444;
    g_current_theme.text = 0xFFE0E0E0;
    g_current_theme.text_secondary = 0xFF888888;
    g_current_theme.widget_bg = 0xFF2A2A2A;
    g_current_theme.widget_bg_hover = 0xFF3A3A3A;
    g_current_theme.widget_bg_pressed = 0xFF1A1A1A;
    
    g_current_theme.success = 0xFF00DD00;
    g_current_theme.warning = 0xFFFFDD00;
    g_current_theme.error = 0xFFFF3333;
    g_current_theme.info = 0xFF33CCFF;
    
    g_current_theme.shadow = 0xFF000000;
    g_current_theme.shadow_alpha = 200;
}

void init_light_theme() {
    g_current_theme.background = 0xFFF5F5F5;
    g_current_theme.foreground = 0xFF333333;
    g_current_theme.accent = 0xFF0066FF;
    g_current_theme.accent_light = 0xFF3399FF;
    g_current_theme.accent_dark = 0xFF0033CC;
    
    g_current_theme.border = 0xFFDDDDDD;
    g_current_theme.text = 0xFF333333;
    g_current_theme.text_secondary = 0xFF777777;
    g_current_theme.widget_bg = 0xFFFFFFFF;
    g_current_theme.widget_bg_hover = 0xFFF0F0F0;
    g_current_theme.widget_bg_pressed = 0xFFE0E0E0;
    
    g_current_theme.success = 0xFF00AA00;
    g_current_theme.warning = 0xFFCC9900;
    g_current_theme.error = 0xFFCC0000;
    g_current_theme.info = 0xFF0099CC;
    
    g_current_theme.shadow = 0xFF000000;
    g_current_theme.shadow_alpha = 64;
}

} // namespace acos::gui
