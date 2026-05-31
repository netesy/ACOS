#pragma once
#include "widget.h"

namespace acos::gui {

class Button : public Widget {
public:
    Button(const char* label);
    void draw(u32* buffer, u32 pitch) override;
    void handle_event(const acos::input::InputEvent& event) override;

    typedef void (*OnClick)();
    void set_on_click(OnClick handler) { m_on_click = handler; }

private:
    const char* m_label;
    OnClick m_on_click;
    bool m_pressed;
};

} // namespace acos::gui
