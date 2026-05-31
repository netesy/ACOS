#pragma once
#include "widget.h"

namespace acos::gui {

class TextBox : public Widget {
public:
    TextBox();
    void draw(u32* buffer, u32 pitch) override;
    void handle_event(const acos::input::InputEvent& event) override;

    const char* text() const { return m_buffer; }
    void set_text(const char* text);

private:
    char m_buffer[256];
    usize m_cursor;
};

} // namespace acos::gui
