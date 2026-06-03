#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui {

class ColorPicker : public Widget {
public:
    ColorPicker();
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    u32 selected_color() const { return m_color; }
    Signal<u32> on_color_changed;

private:
    u32 m_color;
};

} // namespace acos::gui
