#pragma once
#include "widget.h"

namespace acos::gui::widgets {

enum class Orientation {
    Horizontal,
    Vertical
};

class ScrollBar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    ScrollBar(Orientation orientation = Orientation::Vertical);
    virtual ~ScrollBar();

    ::acos::i32 value() const { return m_value; }
    void set_value(::acos::i32 value);
    void set_range(::acos::i32 min, ::acos::i32 max, ::acos::i32 page_size);

private:
    [[maybe_unused]] Orientation m_orientation;
    ::acos::i32 m_value;
    ::acos::i32 m_min;
    ::acos::i32 m_max;
    ::acos::i32 m_page_size;
    [[maybe_unused]] bool m_dragging;
    [[maybe_unused]] ::acos::i32 m_drag_start;
};

} // namespace acos::gui::widgets
