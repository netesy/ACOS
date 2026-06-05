#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui::widgets {

class SpinBox : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    SpinBox(i32 min = 0, i32 max = 100);
    virtual ~SpinBox();


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

} // namespace acos::gui::widgets
