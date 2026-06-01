#pragma once
#include "widget.h"

namespace acos::gui {

class Button : public Widget {
public:
    Button(const char* label);
    ~Button();
    
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;
    void update(u64 delta_ms) override;

    // Callbacks
    typedef void (*OnClick)(Button* btn);
    void set_on_click(OnClick handler) { m_on_click = handler; }
    
    // Styling
    void set_label(const char* label) { m_label = label; }
    const char* label() const { return m_label; }
    
    void set_background_color(u32 color) { m_bg_color = color; }
    void set_text_color(u32 color) { m_text_color = color; }
    void set_hover_color(u32 color) { m_hover_color = color; }
    void set_pressed_color(u32 color) { m_pressed_color = color; }

private:
    const char* m_label;
    OnClick m_on_click;
    u32 m_bg_color;
    u32 m_text_color;
    u32 m_hover_color;
    u32 m_pressed_color;
    bool m_mouse_over;
    u64 m_press_time;
};

} // namespace acos::gui
