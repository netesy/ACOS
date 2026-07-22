#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/font.h>
#include <acos/font_manager.h>
#include <acos/renderer.h>
#include "../button.h"
#include "../text.h"
#include "../textbox.h"
#include "../checkbox.h"
#include "../slider.h"
#include "../switch.h"
#include "../radiobutton.h"
#include "../progressbar.h"
#include "../panel.h"
#include "../icon.h"
#include "../listview.h"
#include "../textarea.h"
#include "render_object.h"
#include "context.h"
#include "stack.h"
#include "grid.h"
#include "render_widgets.h"
#include "../theme.h"

namespace acos::gui::widgets {

RenderButton::RenderButton() : m_label(nullptr), m_pressed(false), m_hovered(false) {}
void RenderButton::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 bg_color = m_style.background_color == 0 ? g_current_theme.widget_bg : m_style.background_color;
    ::acos::u8 alpha = m_pressed ? 255 : (m_hovered ? 220 : 200);
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, (bg_color & 0x00FFFFFF) | ((::acos::u32)alpha << 24));
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    if (m_label) {
        ::acos::u32 lw, lh;
        renderer->measure_text(m_label, lw, lh);
        renderer->draw_text(m_label, m_rect.x + (m_rect.w - lw) / 2, m_rect.y + (m_rect.h - lh) / 2, m_style.foreground_color);
    }
}
void RenderButton::perform_layout(BoxConstraints constraints) {
    u32 mw = 80, mh = 32;
    if (m_label) {
        const ::acos::graphics::Font* font = ::acos::graphics::FontManager::get_ui_font();
        if (font) {
            mw = (::acos::u32)(::strlen(m_label) * font->width()) + 24;
            mh = font->height() + 16;
        }
    }
    Size size = constraints.constrain({(i32)mw, (i32)mh});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderButton::set_label(const char* label) { m_label = label; }
void RenderButton::set_pressed(bool pressed) { m_pressed = pressed; }
void RenderButton::set_hovered(bool hovered) { m_hovered = hovered; }

RenderText::RenderText() : m_text(nullptr), m_align(TextAlignment::Left) {}
void RenderText::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer || !m_text) return;

    ::acos::i32 x = m_rect.x;
    u32 measured_w, measured_h;
    renderer->measure_text(m_text, measured_w, measured_h);

    ::acos::i32 y = m_rect.y + (m_rect.h - (i32)measured_h) / 2;

    ::acos::u32 color = m_style.foreground_color == 0 ? g_current_theme.text : m_style.foreground_color;
    renderer->draw_text(m_text, (u32)x, (u32)y, color);
}
void RenderText::perform_layout(BoxConstraints constraints) {
    u32 mw = 0, mh = 0;
    if (m_text) {
        const ::acos::graphics::Font* font = ::acos::graphics::FontManager::get_ui_font();
        if (font) {
            mw = (::acos::u32)(::strlen(m_text) * font->width());
            mh = font->height();
        }
    }
    Size size = constraints.constrain({(i32)mw, (i32)mh});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderText::set_text(const char* text) { m_text = text; }

RenderIcon::RenderIcon() : m_type(IconType::Terminal), m_active(false) {}
void RenderIcon::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    if (m_style.background_color != 0) {
        renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.background_color);
    }

    ::acos::u32 color = m_active ? g_current_theme.primary : g_current_theme.text;

    switch(m_type) {
        case IconType::Terminal: {
            renderer->fill_rounded_rect(m_rect.x + 2, m_rect.y + 2, m_rect.w - 4, m_rect.h - 4, 4, 0xFF1E1E24);
            renderer->draw_rounded_rect(m_rect.x + 2, m_rect.y + 2, m_rect.w - 4, m_rect.h - 4, 4, 0xFF4A90E2);
            renderer->draw_text(">_", m_rect.x + 8, m_rect.y + 12, 0xFF00FF66);
            break;
        }
        case IconType::Files: {
            renderer->fill_rounded_rect(m_rect.x + 4, m_rect.y + 8, m_rect.w - 8, m_rect.h - 14, 3, 0xFFF5A623);
            renderer->fill_rect(m_rect.x + 4, m_rect.y + 4, 16, 6, 0xFFF5A623);
            renderer->draw_rounded_rect(m_rect.x + 4, m_rect.y + 8, m_rect.w - 8, m_rect.h - 14, 3, 0xFFD0021B);
            break;
        }
        case IconType::Monitor: {
            renderer->fill_rounded_rect(m_rect.x + 2, m_rect.y + 4, m_rect.w - 4, m_rect.h - 14, 4, 0xFF00AAFF);
            renderer->draw_rounded_rect(m_rect.x + 2, m_rect.y + 4, m_rect.w - 4, m_rect.h - 14, 4, 0xFFFFFFFF);
            renderer->fill_rect(m_rect.x + (m_rect.w/2) - 3, m_rect.y + m_rect.h - 10, 6, 8, 0xFF888888);
            renderer->fill_rect(m_rect.x + (m_rect.w/2) - 12, m_rect.y + m_rect.h - 4, 24, 3, 0xFF888888);
            break;
        }
        case IconType::Settings: {
            renderer->fill_circle(m_rect.x + m_rect.w/2, m_rect.y + m_rect.h/2, 12, 0xFF9B9B9B);
            renderer->fill_rect(m_rect.x + m_rect.w/2 - 3, m_rect.y + 2, 6, 4, 0xFF9B9B9B);
            renderer->fill_rect(m_rect.x + m_rect.w/2 - 3, m_rect.y + m_rect.h - 6, 6, 4, 0xFF9B9B9B);
            renderer->fill_rect(m_rect.x + 2, m_rect.y + m_rect.h/2 - 3, 4, 6, 0xFF9B9B9B);
            renderer->fill_rect(m_rect.x + m_rect.w - 6, m_rect.y + m_rect.h/2 - 3, 4, 6, 0xFF9B9B9B);
            renderer->fill_circle(m_rect.x + m_rect.w/2, m_rect.y + m_rect.h/2, 6, 0xFF1E1E24);
            break;
        }
        case IconType::Battery: {
            renderer->fill_circle(m_rect.x + m_rect.w/2, m_rect.y + m_rect.h/2, 14, 0xFFD0021B);
            renderer->draw_circle(m_rect.x + m_rect.w/2, m_rect.y + m_rect.h/2, 8, 0xFFFFFFFF);
            renderer->fill_rect(m_rect.x + m_rect.w/2 - 2, m_rect.y + m_rect.h/2 - 10, 4, 10, 0xFFFFFFFF);
            break;
        }
        default:
            renderer->draw_rect(m_rect.x + 10, m_rect.y + 10, m_rect.w - 20, m_rect.h - 20, color);
            break;
    }
}
void RenderIcon::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({24, 24});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderIcon::set_type(IconType type) { m_type = type; }
void RenderIcon::set_active(bool active) { m_active = active; }

RenderCheckBox::RenderCheckBox() : m_label(nullptr), m_checked(false) {}
void RenderCheckBox::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 bx = m_rect.x + 2;
    ::acos::u32 by = m_rect.y + (m_rect.h - 16) / 2;
    ::acos::u32 box_size = 16;
    renderer->blend_rect(bx, by, box_size, box_size, m_style.background_color, 150);
    renderer->draw_rect(bx, by, box_size, box_size, m_style.border_color);
    if (m_checked) {
        renderer->fill_rect(bx + 4, by + 4, box_size - 8, box_size - 8, g_current_theme.primary);
    }
    if (m_label) {
        renderer->draw_text(m_label, bx + box_size + 8, m_rect.y + (m_rect.h - 16) / 2, m_style.foreground_color);
    }
}
void RenderCheckBox::perform_layout(BoxConstraints constraints) {
    u32 mw = 100, mh = 24;
    Size size = constraints.constrain({(i32)mw, (i32)mh});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderCheckBox::set_label(const char* label) { m_label = label; }
void RenderCheckBox::set_checked(bool checked) { m_checked = checked; }

RenderSlider::RenderSlider() : m_value(0.5f), m_min(0), m_max(1.0f) {}
void RenderSlider::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 track_h = 4;
    ::acos::u32 track_y = m_rect.y + (m_rect.h - track_h) / 2;
    renderer->blend_rect(m_rect.x, track_y, m_rect.w, track_h, m_style.background_color, 150);
    ::acos::u32 handle_x = m_rect.x + (::acos::u32)((m_value - m_min) / (m_max - m_min) * (m_rect.w - 12));
    renderer->fill_rounded_rect(handle_x, m_rect.y + (m_rect.h - 12) / 2, 12, 12, 6, g_current_theme.primary);
}
void RenderSlider::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({120, 24});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderSlider::set_value(float v) { m_value = v; }
void RenderSlider::set_range(float min, float max) { m_min = min; m_max = max; }

RenderSwitch::RenderSwitch() : m_label(nullptr), m_on(false) {}
void RenderSwitch::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 sw = 40, sh = 20;
    ::acos::u32 sx = m_rect.x, sy = m_rect.y + (m_rect.h - sh) / 2;
    renderer->fill_rounded_rect(sx, sy, sw, sh, 10, m_on ? g_current_theme.primary : 0xFF444444);
    ::acos::u32 tx = m_on ? sx + sw - 18 : sx + 2;
    renderer->fill_circle(tx + 8, sy + 10, 8, 0xFFFFFFFF);
}
void RenderSwitch::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({40, 24});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderSwitch::set_label(const char* label) { m_label = label; }
void RenderSwitch::set_on(bool on) { m_on = on; }

RenderRadioButton::RenderRadioButton() : m_label(nullptr), m_selected(false) {}
void RenderRadioButton::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 radius = 8;
    renderer->blend_rect(m_rect.x, m_rect.y, radius*2, radius*2, m_style.background_color, 150);
    renderer->draw_circle(m_rect.x + radius, m_rect.y + radius, radius, m_style.border_color);
    if (m_selected) {
        renderer->fill_circle(m_rect.x + radius, m_rect.y + radius, radius - 4, g_current_theme.primary);
    }
    if (m_label) {
        renderer->draw_text(m_label, m_rect.x + radius*2 + 8, m_rect.y + (m_rect.h - 16) / 2, m_style.foreground_color);
    }
}
void RenderRadioButton::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({100, 24});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderRadioButton::set_label(const char* label) { m_label = label; }
void RenderRadioButton::set_selected(bool selected) { m_selected = selected; }

RenderProgressBar::RenderProgressBar() : m_value(0), m_min(0), m_max(100) {}
void RenderProgressBar::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF333333);
    float progress = (m_value - m_min) / (m_max - m_min);
    ::acos::u32 pw = (::acos::u32)(progress * m_rect.w);
    renderer->fill_rect(m_rect.x, m_rect.y, pw, m_rect.h, g_current_theme.primary);
}
void RenderProgressBar::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({200, 8});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderProgressBar::set_value(float v) { m_value = v; }
void RenderProgressBar::set_range(float min, float max) { m_min = min; m_max = max; }

RenderPanel::RenderPanel() : m_is_glass(false) {}
void RenderPanel::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    if (m_style.background_color != 0) {
        if (m_is_glass && m_style.border_radius > 0) {
            ::acos::u32 bg = m_style.background_color;
            ::acos::u8 alpha = (::acos::u8)((bg >> 24) & 0xFF);
            renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, bg, alpha);
        } else {
            renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.background_color);
        }
    }
    if (m_style.border_width > 0) {
        renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    }
    for (auto& child : m_children) {
        if (child) child->paint(renderer);
    }
}
void RenderPanel::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;

    for (auto& child : m_children) {
        if (child) child->perform_layout(BoxConstraints::loose(size.w, size.h));
    }
}
void RenderPanel::set_glass(bool glass) { m_is_glass = glass; }

RenderStack::RenderStack() {}
void RenderStack::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 150);
}
void RenderStack::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
    for (auto& child : m_children) {
        if (child) child->perform_layout(BoxConstraints::loose(size.w, size.h));
    }
}

RenderGrid::RenderGrid() {}
void RenderGrid::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 120);
}
void RenderGrid::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
    for (auto& child : m_children) {
        if (child) child->perform_layout(BoxConstraints::loose(size.w, size.h));
    }
}

RenderListView::RenderListView() : m_count(0), m_selected(-1) {}
void RenderListView::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 180);
    renderer->draw_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_color);

    for (::acos::usize i = 0; i < m_count; ++i) {
        if (m_items[i]) {
            ::acos::i32 item_y = m_rect.y + static_cast<::acos::i32>(i * 20);
            if (item_y + 20 > m_rect.y + m_rect.h) break;

            if (static_cast<::acos::i32>(i) == m_selected) {
                renderer->fill_rect(m_rect.x + 2, item_y + 2, m_rect.w - 4, 18, 0xFF4A90E2); // Highlight blue
            }
            renderer->draw_text(m_items[i], m_rect.x + 8, item_y + 2, 0xFFFFFFFF);
        }
    }
}
void RenderListView::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderListView::set_items(const char** items, ::acos::usize count) {
    for(::acos::usize i=0; i<count && i < 64; ++i) m_items[i] = items[i];
    m_count = count;
}
void RenderListView::set_selected(::acos::i32 index) { m_selected = index; }

RenderTextArea::RenderTextArea() : m_cursor_pos(0), m_cursor_visible(false) { m_text[0] = '\0'; }
void RenderTextArea::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF111111);
    renderer->draw_text(m_text, m_rect.x + 4, m_rect.y + 4, 0xFFFFFFFF);
    (void)m_cursor_pos;
    (void)m_cursor_visible;
}
void RenderTextArea::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderTextArea::set_text(const char* text) { if(text) ::memcpy(m_text, text, ::strlen(text)+1); }
void RenderTextArea::set_cursor(::acos::u32 pos, bool visible) { m_cursor_pos = pos; m_cursor_visible = visible; }

RenderTextBox::RenderTextBox() : m_text(nullptr), m_placeholder(nullptr), m_cursor(0), m_cursor_visible(false) {}
void RenderTextBox::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF222222);
    if (m_text) renderer->draw_text(m_text, m_rect.x + 4, m_rect.y + 4, 0xFFFFFFFF);
    (void)m_placeholder;
    (void)m_cursor;
    (void)m_cursor_visible;
}
void RenderTextBox::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({200, 32});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderTextBox::set_text(const char* text) { m_text = text; }
void RenderTextBox::set_placeholder(const char* placeholder) { m_placeholder = placeholder; }
void RenderTextBox::set_cursor(::acos::u32 cursor, bool visible) { m_cursor = cursor; m_cursor_visible = visible; }

RenderGraph::RenderGraph() : m_count(0) {}
void RenderGraph::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF000000);
    (void)m_data;
    (void)m_count;
}
void RenderGraph::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderGraph::set_data(const float* data, ::acos::u32 count) {
    for(::acos::u32 i=0; i<count && i < 64; ++i) m_data[i] = data[i];
    m_count = count;
}

RenderBadge::RenderBadge() : m_text(nullptr) {}
void RenderBadge::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, 0xFFFF0000);
    (void)m_text;
}
void RenderBadge::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({20, 16});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderBadge::set_text(const char* text) { m_text = text; }

} // namespace acos::gui::widgets
