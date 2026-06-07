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
    if (m_label) renderer->draw_text(m_label, m_rect.x + 10, m_rect.y + 8, m_style.foreground_color);
}
void RenderButton::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderButton::set_label(const char* label) { m_label = label; }
void RenderButton::set_pressed(bool pressed) { m_pressed = pressed; }
void RenderButton::set_hovered(bool hovered) { m_hovered = hovered; }

RenderText::RenderText() : m_text(nullptr), m_align(TextAlignment::Left) {}
void RenderText::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer || !m_text) return;

    ::acos::graphics::Font::Alignment font_align = ::acos::graphics::Font::Alignment::Left;
    if (m_align == TextAlignment::Center) font_align = ::acos::graphics::Font::Alignment::Center;
    else if (m_align == TextAlignment::Right) font_align = ::acos::graphics::Font::Alignment::Right;

    ::acos::i32 x = m_rect.x;
    if (m_align == TextAlignment::Center) x += m_rect.w / 2;
    else if (m_align == TextAlignment::Right) x += m_rect.w;

    u32 measured_w, measured_h;
    renderer->measure_text(m_text, measured_w, measured_h);

    // Vertically center the text within the assigned rect
    ::acos::i32 y = m_rect.y + (m_rect.h - (i32)measured_h) / 2;

    renderer->draw_text(m_text, (u32)x, (u32)y, m_style.foreground_color, font_align);
}
void RenderText::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderText::set_text(const char* text) { m_text = text; }

RenderIcon::RenderIcon() : m_type(IconType::Terminal), m_active(false) {}
void RenderIcon::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 color = m_active ? g_current_theme.primary : g_current_theme.text;

    switch(m_type) {
        case IconType::Terminal:
            renderer->draw_rounded_rect(m_rect.x + 4, m_rect.y + 4, m_rect.w - 8, m_rect.h - 8, 2, color);
            renderer->draw_text(">", m_rect.x + 8, m_rect.y + 8, color);
            break;
        case IconType::Files:
            renderer->fill_rect(m_rect.x + 6, m_rect.y + 6, m_rect.w - 12, m_rect.h - 12, color);
            break;
        case IconType::Code:
            renderer->draw_text("</>", m_rect.x + 4, m_rect.y + 8, color);
            break;
        case IconType::Settings:
            renderer->draw_circle(m_rect.x + m_rect.w/2, m_rect.y + m_rect.h/2, m_rect.w/3, color);
            break;
        default:
            renderer->draw_rect(m_rect.x + 4, m_rect.y + 4, m_rect.w - 8, m_rect.h - 8, color);
            break;
    }
}
void RenderIcon::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderIcon::set_type(IconType type) { m_type = type; }
void RenderIcon::set_active(bool active) { m_active = active; }

RenderCheckBox::RenderCheckBox() : m_label(nullptr), m_checked(false) {}
void RenderCheckBox::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 box_size = 18;
    ::acos::i32 bx = m_rect.x, by = m_rect.y + (m_rect.h - box_size) / 2;
    renderer->blend_rect(bx, by, box_size, box_size, m_style.background_color, 150);
    renderer->draw_rounded_rect(bx, by, box_size, box_size, 4, m_style.border_color);
    if (m_checked) {
        renderer->draw_line(bx + 4, by + 4, bx + box_size - 4, by + box_size - 4, m_style.foreground_color);
        renderer->draw_line(bx + 4, by + box_size - 4, bx + box_size - 4, by + 4, m_style.foreground_color);
    }
    if (m_label) renderer->draw_text(m_label, bx + box_size + 8, m_rect.y + (m_rect.h / 2) - 8, m_style.foreground_color);
}
void RenderCheckBox::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderCheckBox::set_label(const char* label) { m_label = label; }
void RenderCheckBox::set_checked(bool checked) { m_checked = checked; }

RenderSlider::RenderSlider() : m_value(0.0f), m_min(0.0f), m_max(100.0f) {}
void RenderSlider::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::i32 track_h = 4, track_y = m_rect.y + (m_rect.h - track_h) / 2;
    renderer->blend_rect(m_rect.x, track_y, m_rect.w, track_h, m_style.background_color, 150);
    renderer->draw_rounded_rect(m_rect.x, track_y, m_rect.w, track_h, track_h / 2, m_style.border_color);
    float ratio = (m_value - m_min) / (m_max - m_min);
    ::acos::u32 active_w = static_cast<::acos::u32>(m_rect.w * ratio);
    if (active_w > 0) renderer->fill_rect(m_rect.x, track_y, active_w, track_h, m_style.foreground_color);
    ::acos::u32 knob_size = 14;
    ::acos::i32 knob_x = m_rect.x + (::acos::i32)(m_rect.w * ratio) - (::acos::i32)knob_size / 2, knob_y = m_rect.y + (m_rect.h - (::acos::i32)knob_size) / 2;
    renderer->fill_circle(knob_x + (::acos::i32)knob_size / 2, knob_y + (::acos::i32)knob_size / 2, knob_size / 2, m_style.foreground_color);
}
void RenderSlider::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderSlider::set_value(float v) { m_value = v; }
void RenderSlider::set_range(float min, float max) { m_min = min; m_max = max; }

RenderSwitch::RenderSwitch() : m_label(nullptr), m_on(false) {}
void RenderSwitch::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 sw_w = 40, sw_h = 20;
    ::acos::i32 sx = m_rect.x, sy = m_rect.y + (m_rect.h - (::acos::i32)sw_h) / 2;
    ::acos::u32 bg = m_on ? m_style.foreground_color : m_style.background_color;
    renderer->fill_rounded_rect(sx, sy, sw_w, sw_h, sw_h / 2, bg);
    ::acos::u32 knob_color = 0xFFFFFFFF;
    ::acos::i32 knob_x = m_on ? sx + (::acos::i32)sw_w - (::acos::i32)sw_h + 2 : sx + 2;
    renderer->fill_circle(knob_x + (::acos::i32)(sw_h - 4) / 2, sy + (::acos::i32)sw_h / 2, (sw_h - 4) / 2, knob_color);
    if (m_label) renderer->draw_text(m_label, sx + (::acos::i32)sw_w + 8, m_rect.y + (m_rect.h / 2) - 8, m_style.foreground_color);
}
void RenderSwitch::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderSwitch::set_label(const char* label) { m_label = label; }
void RenderSwitch::set_on(bool on) { m_on = on; }

RenderRadioButton::RenderRadioButton() : m_label(nullptr), m_selected(false) {}
void RenderRadioButton::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 radius = 9;
    ::acos::i32 cx = m_rect.x + (::acos::i32)radius, cy = m_rect.y + m_rect.h / 2;
    renderer->blend_rect(m_rect.x, m_rect.y, radius*2, radius*2, m_style.background_color, 150);
    renderer->draw_circle(cx, cy, radius, m_style.border_color);
    if (m_selected) renderer->fill_circle(cx, cy, 4, m_style.foreground_color);
    if (m_label) renderer->draw_text(m_label, m_rect.x + (::acos::i32)radius*2 + 8, m_rect.y + (m_rect.h / 2) - 8, m_style.foreground_color);
}
void RenderRadioButton::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderRadioButton::set_label(const char* label) { m_label = label; }
void RenderRadioButton::set_selected(bool selected) { m_selected = selected; }

RenderProgressBar::RenderProgressBar() : m_value(0.0f), m_min(0.0f), m_max(100.0f) {}
void RenderProgressBar::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 100);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.h / 2, m_style.border_color);
    float ratio = (m_value - m_min) / (m_max - m_min);
    ::acos::u32 fill_w = static_cast<::acos::u32>(m_rect.w * ratio);
    if (fill_w > 0) {
        ::acos::graphics::Gradient grad;
        grad.start = ::acos::graphics::Color::from_argb(m_style.foreground_color);
        grad.end = ::acos::graphics::Color::from_argb(m_style.foreground_color);
        grad.horizontal = true;
        renderer->draw_gradient_rect(m_rect.x, m_rect.y, fill_w, m_rect.h, grad);
    }
}
void RenderProgressBar::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderProgressBar::set_value(float v) { m_value = v; }
void RenderProgressBar::set_range(float min, float max) { m_min = min; m_max = max; }

RenderStack::RenderStack() {}
void RenderStack::paint(::acos::graphics::Renderer* renderer) {
    for (auto& child : m_children) if (child) child->paint(renderer);
}
void RenderStack::perform_layout(BoxConstraints constraints) {
    m_rect.w = constraints.max_w;
    m_rect.h = constraints.max_h;
    for (auto& child : m_children) {
        if (child) {
            Rect r = child->rect();
            child->set_rect({m_rect.x + r.x, m_rect.y + r.y, r.w, r.h});
            child->perform_layout(constraints);
        }
    }
}

RenderGrid::RenderGrid() : m_columns(1), m_spacing(0) {}
void RenderGrid::paint(::acos::graphics::Renderer* renderer) {
    for (auto& child : m_children) if (child) child->paint(renderer);
}
void RenderGrid::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
    if (m_children.size() == 0 || m_columns == 0) return;

    ::acos::i32 cell_w = (m_rect.w - (::acos::i32)(m_columns - 1) * m_spacing) / (::acos::i32)m_columns;
    ::acos::i32 cell_h = cell_w;

    for (::acos::u32 i = 0; i < m_children.size(); i++) {
        auto& child = m_children[i];
        if (!child) continue;
        ::acos::u32 col = i % m_columns;
        ::acos::u32 row = i / m_columns;
        ::acos::i32 cx = m_rect.x + (::acos::i32)col * (cell_w + m_spacing);
        ::acos::i32 cy = m_rect.y + (::acos::i32)row * (cell_h + m_spacing);
        child->set_rect({cx, cy, cell_w, cell_h});
        child->perform_layout(BoxConstraints::tight(cell_w, cell_h));
    }
}

RenderPanel::RenderPanel() : m_is_glass(false) {}
void RenderPanel::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    ::acos::u32 bg = m_style.background_color;
    if (m_is_glass) {
        if (bg == 0) bg = g_current_theme.glass_bg;
        u8 alpha = (u8)((bg >> 24) & 0xFF);
        renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, bg, alpha);
    } else {
        if (bg != 0) renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, bg);
    }

    if (g_current_theme.border_width > 0) {
        renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    }

    for (auto& child : m_children) if (child) child->paint(renderer);
}
void RenderPanel::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
    for (auto& child : m_children) {
        if (child) {
            Rect r = child->rect();
            child->set_rect({m_rect.x + r.x, m_rect.y + r.y, r.w, r.h});
            child->perform_layout(BoxConstraints::loose(m_rect.w, m_rect.h));
        }
    }
}
void RenderPanel::set_glass(bool glass) { m_is_glass = glass; }

RenderListView::RenderListView() : m_count(0), m_selected(-1) {
    for (int i = 0; i < 64; i++) m_items[i] = nullptr;
}
void RenderListView::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 150);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);

    ::acos::i32 item_h = 24;
    for (::acos::usize i = 0; i < m_count; i++) {
        if (!m_items[i]) continue;
        if (i == (::acos::usize)m_selected) {
            renderer->fill_rect(m_rect.x + 2, m_rect.y + 2 + (::acos::i32)i * item_h, m_rect.w - 4, item_h, ::acos::gui::widgets::g_current_theme.primary);
        }
        renderer->draw_text(m_items[i], m_rect.x + 8, m_rect.y + 4 + (::acos::i32)i * item_h, m_style.foreground_color);
    }
}
void RenderListView::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderListView::set_items(const char** items, ::acos::usize count) {
    m_count = count > 64 ? 64 : count;
    for (::acos::usize i = 0; i < m_count; i++) m_items[i] = items[i];
}
void RenderListView::set_selected(::acos::i32 index) { m_selected = index; }

RenderTextArea::RenderTextArea() : m_cursor_pos(0), m_cursor_visible(false) { m_text[0] = '\0'; }
void RenderTextArea::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 120);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);

    const ::acos::i32 padding = 8;
    ::acos::i32 cur_x = m_rect.x + padding;
    ::acos::i32 cur_y = m_rect.y + padding;
    ::acos::i32 line_height = 18;
    ::acos::i32 char_width = 8;
    ::acos::i32 max_chars_per_line = (m_rect.w - padding * 2) / char_width;

    char line_buf[256];
    ::acos::usize line_pos = 0;
    ::acos::u32 char_idx = 0;

    auto flush_line = [&]() {
        line_buf[line_pos] = '\0';
        renderer->draw_text(line_buf, cur_x, cur_y, m_style.foreground_color);
        cur_y += line_height;
        line_pos = 0;
    };

    for (::acos::usize i = 0; m_text[i]; i++, char_idx++) {
        if (m_cursor_visible && char_idx == m_cursor_pos) {
            renderer->draw_line(cur_x + (i32)line_pos * char_width, cur_y, cur_x + (i32)line_pos * char_width, cur_y + 16, 0xFFFFFFFF);
        }

        if (m_text[i] == '\n') {
            flush_line();
        } else {
            line_buf[line_pos++] = m_text[i];
            if ((i32)line_pos >= max_chars_per_line || line_pos >= 255) {
                flush_line();
            }
        }

        if (cur_y > m_rect.y + m_rect.h - line_height) break;
    }

    if (line_pos > 0 && cur_y <= m_rect.y + m_rect.h - line_height) {
        line_buf[line_pos] = '\0';
        renderer->draw_text(line_buf, cur_x, cur_y, m_style.foreground_color);
    }

    if (m_cursor_visible && char_idx == m_cursor_pos && cur_y <= m_rect.y + m_rect.h - line_height) {
        renderer->draw_line(cur_x + (i32)line_pos * char_width, cur_y, cur_x + (i32)line_pos * char_width, cur_y + 16, 0xFFFFFFFF);
    }
}
void RenderTextArea::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderTextArea::set_text(const char* text) {
    if (!text) { m_text[0] = '\0'; return; }
    ::acos::usize i = 0;
    while (text[i] && i < 4095) { m_text[i] = text[i]; i++; }
    m_text[i] = '\0';
}
void RenderTextArea::set_cursor(::acos::u32 pos, bool visible) {
    m_cursor_pos = pos;
    m_cursor_visible = visible;
}

RenderTextBox::RenderTextBox() : m_text(nullptr), m_placeholder(nullptr), m_cursor(0), m_cursor_visible(false) {}
void RenderTextBox::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 180);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    if (m_text && m_text[0] != '\0') renderer->draw_text(m_text, m_rect.x + 8, m_rect.y + 8, m_style.foreground_color);
    else if (m_placeholder) renderer->draw_text(m_placeholder, m_rect.x + 8, m_rect.y + 8, 0x88888888);
    if (m_cursor_visible) {
        ::acos::u32 char_w = 8;
        ::acos::u32 cursor_x = (::acos::u32)m_rect.x + 8 + (m_cursor * char_w);
        renderer->draw_line(cursor_x, (::acos::u32)m_rect.y + 6, cursor_x, (::acos::u32)m_rect.y + (::acos::u32)m_rect.h - 6, m_style.foreground_color);
    }
}
void RenderTextBox::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderTextBox::set_text(const char* text) { m_text = text; }
void RenderTextBox::set_placeholder(const char* placeholder) { m_placeholder = placeholder; }
void RenderTextBox::set_cursor(::acos::u32 cursor, bool visible) { m_cursor = cursor; m_cursor_visible = visible; }

RenderGraph::RenderGraph() : m_count(0) {}
void RenderGraph::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer || m_count == 0) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0x22000000, 50);

    ::acos::i32 bar_w = m_rect.w / 12; // Always space for 12
    for (::acos::u32 i = 0; i < m_count; i++) {
        ::acos::i32 bar_h = (::acos::i32)(m_rect.h * m_data[i]);
        ::acos::u32 color = (i == m_count - 1) ? g_current_theme.accent : 0xFF555555;
        renderer->fill_rounded_rect(m_rect.x + (::acos::i32)i * bar_w + 2, m_rect.y + m_rect.h - bar_h, bar_w - 4, bar_h, 2, color);
    }
}
void RenderGraph::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;
}
void RenderGraph::set_data(const float* data, ::acos::u32 count) {
    m_count = count > 64 ? 64 : count;
    for (::acos::u32 i = 0; i < m_count; i++) m_data[i] = data[i];
}

RenderBadge::RenderBadge() : m_text(nullptr) {}
void RenderBadge::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.h/2, 0x44FFFFFF);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.h/2, 0x88FFFFFF);
    if (m_text) renderer->draw_text(m_text, m_rect.x + 8, m_rect.y + 4, 0xFFFFFFFF);
}
void RenderBadge::perform_layout(BoxConstraints constraints) {
    m_rect.w = constraints.constrain({80, 20}).w;
    m_rect.h = constraints.constrain({80, 20}).h;
}
void RenderBadge::set_text(const char* text) { m_text = text; }

Ref<RenderObject> Stack::create_render_object() {
    return UIContext::get().region().alloc<RenderStack>();
}

Ref<RenderObject> Grid::create_render_object() {
    return UIContext::get().region().alloc<RenderGrid>();
}

void Stack::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
}

void Grid::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rg = static_cast<RenderGrid*>(render_object.operator->());
    if (rg) {
        rg->set_columns(m_columns);
        rg->set_spacing(m_spacing);
    }
}


} // namespace acos::gui::widgets
