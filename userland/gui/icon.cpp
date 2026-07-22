#include <acos/process.h>
#include <acos/runtime.h>
#include "icon.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "core/animation.h"
#include "theme.h"

namespace acos::gui::widgets {

Icon::Icon(IconType type) : m_type(type), m_color(0xFFFFFFFF), m_active(false), m_animate_on_hover(false), m_scale(1.0f), m_on_click(nullptr) {
    m_rect = {0, 0, 32, 32};
}

Icon::~Icon() {}

void Icon::update(::acos::u64 delta_ms) {
    Widget::update(delta_ms);
    
    if (m_animate_on_hover) {
        float target_scale = (m_state == WidgetState::Hovered || m_state == WidgetState::Pressed) ? 1.2f : 1.0f;
        float diff = target_scale - m_scale;
        if ((diff < 0 ? -diff : diff) > 0.01f) {
            m_scale += diff * 0.2f; // Smooth interpolation
            set_paint_dirty();
        } else {
            m_scale = target_scale;
        }
    }
}

Ref<RenderObject> Icon::create_render_object() {
    return UIContext::get().region().alloc<RenderIcon>();
}

void Icon::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto ri = static_cast<RenderIcon*>(render_object.operator->());
    if (ri) {
        ri->set_type(m_type);
        ri->set_active(m_active);
        ri->set_hovered(m_state == WidgetState::Hovered || m_state == WidgetState::Pressed);
        ri->set_scale(m_scale);
    }
}

void Icon::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        ::acos::i32 mx = event.mouse_x;
        ::acos::i32 my = event.mouse_y;
        bool pressed = (raw.value & 0x01) != 0;

        // Traverse up the parent tree to compute the absolute global screen-space rectangle
        Rect global_rect = m_rect;
        Ref<Widget> p = m_parent;
        while (p) {
            global_rect.x += p->rect().x;
            global_rect.y += p->rect().y;
            p = p->parent();
        }

        if (global_rect.contains(mx, my)) {
            if (!pressed && m_state == WidgetState::Pressed) {
                if (m_on_click) m_on_click(nullptr);
            }
            m_state = pressed ? WidgetState::Pressed : WidgetState::Hovered;
        } else {
            m_state = WidgetState::Normal;
        }
        set_paint_dirty();
    }
}

} // namespace acos::gui::widgets
