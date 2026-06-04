#pragma once
#include "widget.h"

namespace acos::gui {

class TextArea : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    TextArea();
    virtual ~TextArea();

    void update(u64 delta_ms) override;

    void set_text(const char* text);
    const char* text() const { return m_buffer; }

private:
    char m_buffer[4096];
    u32 m_cursor_pos;

    u32 m_cursor_blink_time;
    bool m_cursor_visible;

    void insert_char(char c);
    void backspace();
};

} // namespace acos::gui
