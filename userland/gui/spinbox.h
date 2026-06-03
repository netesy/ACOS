#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui {

class SpinBox : public Widget {
public:
    SpinBox(i32 min = 0, i32 max = 100);
    virtual ~SpinBox();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    i32 value() const { return m_value; }
    void set_value(i32 value);

    Signal<i32> on_value_changed;

private:
    i32 m_value;
    i32 m_min;
    i32 m_max;
    bool m_up_hovered;
    bool m_down_hovered;
};

} // namespace acos::gui
