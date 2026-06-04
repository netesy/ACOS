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

class Flex : public Widget {
public:
    Flex(Axis axis)
        : m_axis(axis),
          m_main_axis_alignment(MainAxisAlignment::Start),
          m_cross_axis_alignment(CrossAxisAlignment::Start) {}

    Size layout(BoxConstraints constraints) override;
    void draw(acos::graphics::Renderer* renderer) override;

    Ref<RenderObject> create_render_object() override;

    Flex& main_axis_alignment(MainAxisAlignment alignment) { m_main_axis_alignment = alignment; return *this; }
    Flex& cross_axis_alignment(CrossAxisAlignment alignment) { m_cross_axis_alignment = alignment; return *this; }

protected:
    Axis m_axis;
    MainAxisAlignment m_main_axis_alignment;
    CrossAxisAlignment m_cross_axis_alignment;
};

class Row : public Flex {
public:
    Row() : Flex(Axis::Horizontal) {}

    // Fluent API
    Row& child(Ref<Widget> c) { add_child(c); return *this; }
};

class Column : public Flex {
public:
    Column() : Flex(Axis::Vertical) {}

    // Fluent API
    Column& child(Ref<Widget> c) { add_child(c); return *this; }
};

} // namespace acos::gui
