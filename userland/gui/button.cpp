#include "button.h"
#include "theme.h"
#include "core/event_dispatcher.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s && s[len]) len++;
    return len;
}

Button::Button(const char* label) 
    : m_label(label), m_mouse_over(false), m_press_time(0) {
    m_rect.w = 100;
    m_rect.h = 32;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Clickable;
    m_state = WidgetState::Normal;
    m_style.elevation = 2;
    
    m_bg_color = g_current_theme.surface;
    m_text_color = g_current_theme.text;
    m_hover_color = g_current_theme.primary;
    m_pressed_color = g_current_theme.secondary;
}

Button::~Button() {}


Ref<RenderObject> Button::create_render_object() {
    return UIContext::get().region().alloc<RenderButton>();
}

void Button::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    if (render_object) {
        RenderButton* rb = static_cast<RenderButton*>(render_object.operator->());
        rb->set_label(m_label);
        rb->set_pressed(m_state == WidgetState::Pressed);
        rb->set_hovered(m_state == WidgetState::Hovered);
    }
}

void Button::update(u64 delta_ms) {
    if (m_state == WidgetState::Pressed) {
        m_press_time += delta_ms;
        if (m_press_time > 100) {
            m_state = m_mouse_over ? WidgetState::Hovered : WidgetState::Normal;
            m_style.elevation = m_mouse_over ? 4 : 2;
        }
    }
}

void Button::on_event(Event& event) {
    if (!(m_flags & (u32)WidgetFlags::Enabled)) return;

    if (event.raw.type == acos::input::InputType::Mouse) {
        bool button_pressed = (event.raw.value & 0x01) != 0;

        if (event.phase == EventPhase::Target) {
            if (button_pressed) {
                m_state = WidgetState::Pressed;
                m_style.elevation = 1;
                m_press_time = 0;
                if (m_on_click) m_on_click(nullptr);
                event.stop_propagation();
            }
        }

        // Handle hovering logic
        i32 mouse_x = event.mouse_x;
        i32 mouse_y = event.mouse_y;
        bool was_over = m_mouse_over;
        m_mouse_over = hit_test(mouse_x, mouse_y);
        
        if (m_mouse_over && !was_over) {
            m_state = WidgetState::Hovered;
            m_style.elevation = 4;
        } else if (!m_mouse_over && was_over) {
            m_state = WidgetState::Normal;
            m_style.elevation = 2;
        }
    }
}

} // namespace acos::gui
