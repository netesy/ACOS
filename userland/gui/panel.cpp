#include <acos/process.h>
#include <acos/runtime.h>
#include "panel.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Panel::Panel() : m_bg_color(0), m_is_glass(false), m_on_click(nullptr) {
    m_rect = {0, 0, 100, 100};
}

Panel::~Panel() {}

Ref<RenderObject> Panel::create_render_object() {
    return UIContext::get().region().alloc<RenderPanel>();
}

void Panel::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rp = static_cast<RenderPanel*>(render_object.operator->());
    if (rp) {
        rp->set_glass(m_is_glass);
    }
}

void Panel::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        bool pressed = (raw.value & 0x01) != 0;

        // Event dispatcher already performed hit testing, so we only receive events when over this widget
        if (!pressed && m_state == WidgetState::Pressed) {
            if (m_on_click) m_on_click(nullptr);
        }
        m_state = pressed ? WidgetState::Pressed : WidgetState::Hovered;
        // Panels don't usually change look on hover unless specifically styled,
        // but we'll trigger paint dirty just in case.
        set_paint_dirty();
    }
}

} // namespace acos::gui::widgets
