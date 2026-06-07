#include "icon.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"
#include "theme.h"

namespace acos::gui::widgets {

Icon::Icon(IconType type) : m_type(type), m_color(0xFFFFFFFF), m_active(false), m_on_click(nullptr) {
    m_rect = {0, 0, 32, 32};
}

Icon::~Icon() {}

Ref<RenderObject> Icon::create_render_object() {
    return UIContext::get().region().alloc<RenderIcon>();
}

void Icon::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto ri = static_cast<RenderIcon*>(render_object.operator->());
    if (ri) {
        ri->set_type(m_type);
        ri->set_active(m_active);
    }
}

void Icon::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::input::InputType::Mouse) {
        ::acos::i32 mx = event.mouse_x;
        ::acos::i32 my = event.mouse_y;
        bool pressed = (raw.value & 0x01) != 0;

        if (m_rect.contains(mx, my)) {
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
