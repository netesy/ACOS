#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class SpinBox : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    SpinBox(::acos::i32 min = 0, ::acos::i32 max = 100);
    virtual ~SpinBox();


    ::acos::i32 value() const { return m_value; }
    void set_value(::acos::i32 value);

private:
    ::acos::i32 m_value;
    ::acos::i32 m_min;
    ::acos::i32 m_max;
    [[maybe_unused]] bool m_up_hovered;
    [[maybe_unused]] bool m_down_hovered;
};

} // namespace acos::gui::widgets
