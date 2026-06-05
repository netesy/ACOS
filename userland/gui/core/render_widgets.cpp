#include "../button.h"
#include "../text.h"
#include "../textbox.h"
#include "../checkbox.h"
#include "../slider.h"
#include "../switch.h"
#include "../radiobutton.h"
#include "../progressbar.h"
#include "../panel.h"
#include "render_object.h"
#include "context.h"
#include "stack.h"
#include "grid.h"
#include "render_widgets.h"

namespace acos::gui::widgets {

RenderButton::RenderButton() : m_label(nullptr), m_pressed(false), m_hovered(false) {}
void RenderButton::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    u32 bg_color = m_style.background_color;
    u8 alpha = m_pressed ? 255 : (m_hovered ? 220 : 200);
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, (bg_color & 0x00FFFFFF) | ((u32)alpha << 24));
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    if (m_label) renderer->draw_text(m_label, m_rect.x + 10, m_rect.y + 8, m_style.foreground_color);
}
void RenderButton::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderButton::set_label(const char* label) { m_label = label; }
void RenderButton::set_pressed(bool pressed) { m_pressed = pressed; }
void RenderButton::set_hovered(bool hovered) { m_hovered = hovered; }

RenderText::RenderText() : m_text(nullptr) {}
void RenderText::paint(acos::graphics::Renderer* renderer) {
    if (!renderer || !m_text) return;
    renderer->draw_text(m_text, m_rect.x, m_rect.y, m_style.foreground_color);
}
void RenderText::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderText::set_text(const char* text) { m_text = text; }

RenderTextBox::RenderTextBox() : m_text(nullptr), m_placeholder(nullptr), m_cursor(0), m_cursor_visible(false) {}
void RenderTextBox::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 180);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    if (m_text && m_text[0] != '\0') renderer->draw_text(m_text, m_rect.x + 8, m_rect.y + 8, m_style.foreground_color);
    else if (m_placeholder) renderer->draw_text(m_placeholder, m_rect.x + 8, m_rect.y + 8, 0x88888888);
    if (m_cursor_visible) {
        u32 char_w = 8;
        u32 cursor_x = m_rect.x + 8 + (m_cursor * char_w);
        renderer->draw_line(cursor_x, m_rect.y + 6, cursor_x, m_rect.y + m_rect.h - 6, m_style.foreground_color);
    }
}
void RenderTextBox::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderTextBox::set_text(const char* text) { m_text = text; }
void RenderTextBox::set_placeholder(const char* placeholder) { m_placeholder = placeholder; }
void RenderTextBox::set_cursor(u32 cursor, bool visible) { m_cursor = cursor; m_cursor_visible = visible; }

RenderCheckBox::RenderCheckBox() : m_label(nullptr), m_checked(false) {}
void RenderCheckBox::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    u32 box_size = 18;
    i32 bx = m_rect.x, by = m_rect.y + (m_rect.h - box_size) / 2;
    renderer->blend_rect(bx, by, box_size, box_size, m_style.background_color, 150);
    renderer->draw_rounded_rect(bx, by, box_size, box_size, 4, m_style.border_color);
    if (m_checked) {
        renderer->draw_line(bx + 4, by + 4, bx + box_size - 4, by + box_size - 4, m_style.foreground_color);
        renderer->draw_line(bx + 4, by + box_size - 4, bx + box_size - 4, by + 4, m_style.foreground_color);
    }
    if (m_label) renderer->draw_text(m_label, bx + box_size + 8, m_rect.y + (m_rect.h / 2) - 8, m_style.foreground_color);
}
void RenderCheckBox::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderCheckBox::set_label(const char* label) { m_label = label; }
void RenderCheckBox::set_checked(bool checked) { m_checked = checked; }

RenderSlider::RenderSlider() : m_value(0.0f), m_min(0.0f), m_max(100.0f) {}
void RenderSlider::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    i32 track_h = 4, track_y = m_rect.y + (m_rect.h - track_h) / 2;
    renderer->blend_rect(m_rect.x, track_y, m_rect.w, track_h, m_style.background_color, 150);
    renderer->draw_rounded_rect(m_rect.x, track_y, m_rect.w, track_h, track_h / 2, m_style.border_color);
    float ratio = (m_value - m_min) / (m_max - m_min);
    u32 active_w = static_cast<u32>(m_rect.w * ratio);
    if (active_w > 0) renderer->fill_rect(m_rect.x, track_y, active_w, track_h, m_style.foreground_color);
    u32 knob_size = 14;
    i32 knob_x = m_rect.x + (i32)(m_rect.w * ratio) - knob_size / 2, knob_y = m_rect.y + (m_rect.h - knob_size) / 2;
    renderer->fill_circle(knob_x + knob_size / 2, knob_y + knob_size / 2, knob_size / 2, m_style.foreground_color);
}
void RenderSlider::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderSlider::set_value(float v) { m_value = v; }
void RenderSlider::set_range(float min, float max) { m_min = min; m_max = max; }

RenderSwitch::RenderSwitch() : m_label(nullptr), m_on(false) {}
void RenderSwitch::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    u32 sw_w = 40, sw_h = 20;
    i32 sx = m_rect.x, sy = m_rect.y + (m_rect.h - sw_h) / 2;
    u32 bg = m_on ? m_style.foreground_color : m_style.background_color;
    renderer->fill_rounded_rect(sx, sy, sw_w, sw_h, sw_h / 2, bg);
    u32 knob_color = 0xFFFFFFFF;
    i32 knob_x = m_on ? sx + sw_w - sw_h + 2 : sx + 2;
    renderer->fill_circle(knob_x + (sw_h - 4) / 2, sy + sw_h / 2, (sw_h - 4) / 2, knob_color);
    if (m_label) renderer->draw_text(m_label, sx + sw_w + 8, m_rect.y + (m_rect.h / 2) - 8, m_style.foreground_color);
}
void RenderSwitch::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderSwitch::set_label(const char* label) { m_label = label; }
void RenderSwitch::set_on(bool on) { m_on = on; }

RenderRadioButton::RenderRadioButton() : m_label(nullptr), m_selected(false) {}
void RenderRadioButton::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    u32 radius = 9;
    i32 cx = m_rect.x + radius, cy = m_rect.y + m_rect.h / 2;
    renderer->blend_rect(m_rect.x, m_rect.y, radius*2, radius*2, m_style.background_color, 150);
    renderer->draw_circle(cx, cy, radius, m_style.border_color);
    if (m_selected) renderer->fill_circle(cx, cy, 4, m_style.foreground_color);
    if (m_label) renderer->draw_text(m_label, m_rect.x + radius*2 + 8, m_rect.y + (m_rect.h / 2) - 8, m_style.foreground_color);
}
void RenderRadioButton::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderRadioButton::set_label(const char* label) { m_label = label; }
void RenderRadioButton::set_selected(bool selected) { m_selected = selected; }

RenderProgressBar::RenderProgressBar() : m_value(0.0f), m_min(0.0f), m_max(100.0f) {}
void RenderProgressBar::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 100);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_rect.h / 2, m_style.border_color);
    float ratio = (m_value - m_min) / (m_max - m_min);
    u32 fill_w = static_cast<u32>(m_rect.w * ratio);
    if (fill_w > 0) {
        acos::graphics::Gradient grad;
        grad.start = acos::graphics::Color::from_argb(m_style.foreground_color);
        grad.end = acos::graphics::Color::from_argb(m_style.foreground_color);
        grad.horizontal = true;
        renderer->draw_gradient_rect(m_rect.x, m_rect.y, fill_w, m_rect.h, grad);
    }
}
void RenderProgressBar::perform_layout(BoxConstraints constraints) { (void)constraints; }
void RenderProgressBar::set_value(float v) { m_value = v; }
void RenderProgressBar::set_range(float min, float max) { m_min = min; m_max = max; }

RenderStack::RenderStack() {}
void RenderStack::paint(acos::graphics::Renderer* renderer) {
    for (auto& child : m_children) if (child) child->paint(renderer);
}
void RenderStack::perform_layout(BoxConstraints constraints) {
    for (auto& child : m_children) if (child) child->perform_layout(constraints);
}

RenderGrid::RenderGrid() {}
void RenderGrid::paint(acos::graphics::Renderer* renderer) {
    for (auto& child : m_children) if (child) child->paint(renderer);
}
void RenderGrid::perform_layout(BoxConstraints constraints) {
    for (auto& child : m_children) if (child) child->perform_layout(constraints);
}

RenderPanel::RenderPanel() : m_is_glass(false) {}
void RenderPanel::paint(acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    if (m_is_glass) renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.background_color, 150);
    else renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.background_color);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, m_style.border_radius, m_style.border_color);
    for (auto& child : m_children) if (child) child->paint(renderer);
}
void RenderPanel::perform_layout(BoxConstraints constraints) {
    for (auto& child : m_children) if (child) child->perform_layout(constraints);
}
void RenderPanel::set_glass(bool glass) { m_is_glass = glass; }

Ref<RenderObject> Stack::create_render_object() {
    return UIContext::get().region().alloc<RenderStack>();
}

Ref<RenderObject> Grid::create_render_object() {
    return UIContext::get().region().alloc<RenderGrid>();
}

} // namespace acos::gui::widgets
