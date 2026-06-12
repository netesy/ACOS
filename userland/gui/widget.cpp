#include <acos/process.h>
#include <acos/runtime.h>
#include "widget.h"
#include "theme.h"
#include "core/context.h"
#include "core/event_dispatcher.h"

namespace acos::gui {

Widget::Widget() : m_rect{0, 0, 0, 0}, m_parent(),
                   m_flags((u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::LayoutDirty | (u32)WidgetFlags::PaintDirty),
                   m_state(WidgetState::Normal), m_style() {
}
Widget::~Widget() {}

void Widget::handle_event(Event& event) {
    // Phase-specific logic can go here.
    // For now, we delegate to the local event handler.
    // We do NOT call handle_event(event.raw) because that would trigger legacy recursion.
    on_event(event);
}


void Widget::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == acos::input::InputType::Keyboard && raw.code == 9 && event.phase == EventPhase::Target) { // Tab key
        // Focus navigation logic should ideally be in FocusManager,
        // but for now we'll move it to use FocusManager.
        Ref<Widget> next_focus;
        u32 count = m_children.size();
        bool found_current = false;
        for (u32 i = 0; i < count; i++) {
            if (m_children[i] && m_children[i]->is_focused()) {
                found_current = true;
                for (u32 j = (i + 1) % count; j != i; j = (j + 1) % count) {
                    if (m_children[j] && m_children[j]->is_focusable()) {
                        next_focus = m_children[j];
                        break;
                    }
                }
                break;
            }
        }
        if (!found_current && count > 0) {
            for (u32 i = 0; i < count; i++) {
                if (m_children[i] && m_children[i]->is_focusable()) {
                    next_focus = m_children[i];
                    break;
                }
            }
        }

        if (next_focus) {
            UIContext::get().focus_manager().set_focus(next_focus);
            event.stop_propagation();
        }
    }
}

void Widget::add_child(Ref<Widget> child) {
    if (child) {
        m_children.push_back(child);
        child->set_parent(self());
        set_layout_dirty();
    }
}

void Widget::update_render_object(Ref<RenderObject> render_object) {
    if (render_object) {
        render_object->set_rect(m_rect);
        render_object->set_style(m_style);
    }
}

Size Widget::layout(BoxConstraints constraints) {
    Size size = constraints.constrain({m_rect.w, m_rect.h});
    m_rect.w = size.w;
    m_rect.h = size.h;

    for (auto& child : m_children) {
        if (child && child->is_visible()) {
            child->layout(BoxConstraints::loose(size.w, size.h));
        }
    }

    clear_layout_dirty();
    return size;
}

Ref<Widget> Widget::self() {
    return UIContext::get().region().get_ref(this);
}

Widget& Widget::background(u32 color) {
    m_style.background_color = color;
    set_paint_dirty();
    return *this;
}

Widget& Widget::opacity(float o) {
    m_style.opacity = o;
    set_paint_dirty();
    return *this;
}

Widget& Widget::radius(u32 r) {
    m_style.border_radius = r;
    set_paint_dirty();
    return *this;
}

Widget& Widget::padding(u32 p) {
    m_style.padding_left = m_style.padding_right = m_style.padding_top = m_style.padding_bottom = p;
    set_layout_dirty();
    return *this;
}

Widget& Widget::padding(u32 top, u32 right, u32 bottom, u32 left) {
    m_style.padding_top = top;
    m_style.padding_right = right;
    m_style.padding_bottom = bottom;
    m_style.padding_left = left;
    set_layout_dirty();
    return *this;
}

Widget& Widget::margin(u32 m) {
    m_style.margin_left = m_style.margin_right = m_style.margin_top = m_style.margin_bottom = m;
    set_layout_dirty();
    return *this;
}

Widget& Widget::margin(u32 top, u32 right, u32 bottom, u32 left) {
    m_style.margin_top = top;
    m_style.margin_right = right;
    m_style.margin_bottom = bottom;
    m_style.margin_left = left;
    set_layout_dirty();
    return *this;
}

Widget& Widget::preferred_size(i32 w, i32 h) {
    m_style.preferred_w = w;
    m_style.preferred_h = h;
    set_layout_dirty();
    return *this;
}

Widget& Widget::preferred_width(i32 w) {
    m_style.preferred_w = w;
    set_layout_dirty();
    return *this;
}

Widget& Widget::preferred_height(i32 h) {
    m_style.preferred_h = h;
    set_layout_dirty();
    return *this;
}

Widget& Widget::flex_grow(u32 factor) {
    m_style.flex_grow = factor;
    set_layout_dirty();
    return *this;
}

Widget& Widget::position(Position pos) {
    m_style.position = pos;
    set_layout_dirty();
    return *this;
}

Widget& Widget::anchor_top(i32 v) {
    m_style.anchor_top = v;
    set_layout_dirty();
    return *this;
}

Widget& Widget::anchor_right(i32 v) {
    m_style.anchor_right = v;
    set_layout_dirty();
    return *this;
}

Widget& Widget::anchor_bottom(i32 v) {
    m_style.anchor_bottom = v;
    set_layout_dirty();
    return *this;
}

Widget& Widget::anchor_left(i32 v) {
    m_style.anchor_left = v;
    set_layout_dirty();
    return *this;
}

Widget& Widget::fixed(i32 top, i32 right, i32 bottom, i32 left) {
    m_style.position   = Position::Fixed;
    m_style.anchor_top    = top;
    m_style.anchor_right  = right;
    m_style.anchor_bottom = bottom;
    m_style.anchor_left   = left;
    set_layout_dirty();
    return *this;
}

Widget& Widget::elevation(u32 e) {
    m_style.elevation = e;
    set_paint_dirty();
    return *this;
}

void Widget::remove_child(Ref<Widget> child) {
    for (u32 i = 0; i < m_children.size(); i++) {
        if (m_children[i] == child) {
            m_children.remove_at(i);
            set_layout_dirty();
            break;
        }
    }
}

void Widget::set_visible(bool v) {
    if (v) m_flags |= (u32)WidgetFlags::Visible;
    else m_flags &= ~(u32)WidgetFlags::Visible;
}

void Widget::set_enabled(bool e) {
    if (e) m_flags |= (u32)WidgetFlags::Enabled;
    else m_flags &= ~(u32)WidgetFlags::Enabled;
}

void Widget::set_focused(bool f) {
    if (f) m_state = WidgetState::Focused;
    else if (m_state == WidgetState::Focused) m_state = WidgetState::Normal;
}

void Widget::update(u64 delta_ms) {
    for (auto& child : m_children) {
        if (child) child->update(delta_ms);
    }
}

void Widget::set_layout_dirty() {
    if (!(m_flags & (u32)WidgetFlags::LayoutDirty)) {
        m_flags |= (u32)WidgetFlags::LayoutDirty;
        if (m_parent) m_parent->set_layout_dirty();
    }
}

void Widget::set_paint_dirty() {
    m_flags |= (u32)WidgetFlags::PaintDirty;
}

void Widget::draw_shadow(acos::graphics::Renderer* renderer) {
    if (m_style.elevation > 0 && renderer) {
        // Material design inspired shadows: depth increases offset and blur (simulated by larger area/lower alpha)
        u32 offset = m_style.elevation;
        u8 alpha = (u8)(g_current_theme.shadow_alpha / m_style.elevation);
        renderer->draw_shadow(m_rect.x, m_rect.y, m_rect.w, m_rect.h, offset, alpha);
    }
}

} // namespace acos::gui
