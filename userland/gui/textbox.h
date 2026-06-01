#pragma once
#include "widget.h"

namespace acos::gui {

class TextBox : public Widget {
public:
    TextBox();
    ~TextBox();
    
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;
    void update(u64 delta_ms) override;

    const char* text() const { return m_buffer; }
    void set_text(const char* text);
    void clear();
    
    void set_placeholder(const char* text) { m_placeholder = text; }
    void set_max_length(usize len) { m_max_length = len; }
    void set_text_color(u32 color) { m_text_color = color; }
    void set_background_color(u32 color) { m_bg_color = color; }

private:
    char m_buffer[512];
    usize m_cursor;
    usize m_max_length;
    const char* m_placeholder;
    u32 m_text_color;
    u32 m_bg_color;
    u64 m_cursor_blink_time;
    bool m_cursor_visible;
};

} // namespace acos::gui
