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

void Button::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible)) return;
    
    draw_shadow(renderer);

    u32 bg_color = m_bg_color;
    u8 alpha = 200;

    if (m_state == WidgetState::Pressed) {
        bg_color = m_pressed_color;
        alpha = 255;
    } else if (m_state == WidgetState::Hovered) {
        bg_color = m_hover_color;
        alpha = 220;
    }
    
    renderer->fill_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, (bg_color & 0x00FFFFFF) | ((u32)alpha << 24));
    
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, g_current_theme.border);
    
    if (m_label) {
        u32 char_w = 8;
        u32 char_h = 16;
        if (acos::graphics::Font::get_default()) {
            char_w = acos::graphics::Font::get_default()->width();
            char_h = acos::graphics::Font::get_default()->height();
        }

        i32 text_x = m_rect.x + (m_rect.w / 2) - (i32)(strlen_impl(m_label) * char_w / 2);
        i32 text_y = m_rect.y + (m_rect.h / 2) - (i32)(char_h / 2);
        renderer->draw_text(m_label, (u32)text_x, (u32)text_y, m_text_color);
    }
}

void Button::handle_event(const acos::input::InputEvent& event) {
    // Legacy support: call on_event with a synthetic Event if needed,
    // but better to just let the dispatcher handle it now.
    // For now, we do nothing to prevent redundant handling if dispatcher is active.
}

Ref<RenderObject> Button::create_render_object() {
    return UIContext::get().region().alloc<RenderButton>();
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
                m_on_click_signal.emit();
                event.stop_propagation();
            }
        }

        // Handle hovering logic
        i32 mouse_x = event.raw.x;
        i32 mouse_y = event.raw.y;
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
