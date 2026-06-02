#pragma once
#include "widget.h"

namespace acos::gui {

enum class Orientation {
    Horizontal,
    Vertical
};

class ScrollBar : public Widget {
public:
    ScrollBar(Orientation orientation = Orientation::Vertical);
    virtual ~ScrollBar();

    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    i32 value() const { return m_value; }
    void set_value(i32 value);
    void set_range(i32 min, i32 max, i32 page_size);

private:
    Orientation m_orientation;
    i32 m_value;
    i32 m_min;
    i32 m_max;
    i32 m_page_size;
    bool m_dragging;
    i32 m_drag_start;
};

} // namespace acos::gui
