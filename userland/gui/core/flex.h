#pragma once
#include "../widget.h"

namespace acos::gui {

enum class MainAxisAlignment {
    Start,
    Center,
    End,
    SpaceBetween,
    SpaceAround,
    SpaceEvenly
};

enum class CrossAxisAlignment {
    Start,
    Center,
    End,
    Stretch
};

enum class Axis {
    Horizontal,
    Vertical
};

namespace widgets {

class Flex : public Widget {
public:
    Flex(::acos::gui::Axis axis)
        : m_axis(axis),
          m_main_axis_alignment(::acos::gui::MainAxisAlignment::Start),
          m_cross_axis_alignment(::acos::gui::CrossAxisAlignment::Start) {}

    Size layout(BoxConstraints constraints) override;

    Ref<RenderObject> create_render_object() override;

    Flex& main_axis_alignment(::acos::gui::MainAxisAlignment alignment) { m_main_axis_alignment = alignment; return *this; }
    Flex& cross_axis_alignment(::acos::gui::CrossAxisAlignment alignment) { m_cross_axis_alignment = alignment; return *this; }

protected:
    ::acos::gui::Axis m_axis;
    ::acos::gui::MainAxisAlignment m_main_axis_alignment;
    ::acos::gui::CrossAxisAlignment m_cross_axis_alignment;
};

class Row : public Flex {
public:
    Row() : Flex(::acos::gui::Axis::Horizontal) {}

    // Internal Fluent API
    Row& child(Ref<Widget> c) { add_child(c); return *this; }
};

class Column : public Flex {
public:
    Column() : Flex(::acos::gui::Axis::Vertical) {}

    // Internal Fluent API
    Column& child(Ref<Widget> c) { add_child(c); return *this; }
};

} // namespace widgets
} // namespace acos::gui
