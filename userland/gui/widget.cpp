#include "widget.h"
#include "theme.h"
#include "core/context.h"

namespace acos::gui {

Widget::Widget() : m_rect{0, 0, 0, 0}, m_parent(),
                   m_flags((u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::LayoutDirty | (u32)WidgetFlags::PaintDirty),
                   m_state(WidgetState::Normal), m_elevation(0) {
}
Widget::~Widget() {}

void Widget::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Keyboard && event.code == 9) { // Tab key
        bool found_current = false;
        u32 count = m_children.size();
        for (u32 i = 0; i < count; i++) {
            if (m_children[i] && m_children[i]->is_focused()) {
                m_children[i]->set_focused(false);
                found_current = true;
                for (u32 j = (i + 1) % count; j != i; j = (j + 1) % count) {
                    if (m_children[j] && (m_children[j]->is_focusable())) {
                        m_children[j]->set_focused(true);
                        return;
                    }
                }
                break;
            }
        }
        if (!found_current && count > 0) {
            for (u32 i = 0; i < count; i++) {
                if (m_children[i] && (m_children[i]->is_focusable())) {
                    m_children[i]->set_focused(true);
                    return;
                }
            }
        }
    }

    for (auto& child : m_children) {
        if (child && child->is_enabled()) {
            child->handle_event(event);
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

Ref<Widget> Widget::self() {
    return UIContext::get().region().get_ref(this);
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
    if (m_elevation > 0 && renderer) {
        // Material design inspired shadows: depth increases offset and blur (simulated by larger area/lower alpha)
        u32 offset = m_elevation;
        u8 alpha = (u8)(g_current_theme.shadow_alpha / m_elevation);
        renderer->draw_shadow(m_rect.x, m_rect.y, m_rect.w, m_rect.h, offset, alpha);
    }
}

} // namespace acos::gui
