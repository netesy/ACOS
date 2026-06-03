#pragma once
#include <ui/geometry.h>
#include <ui/ref.h>

namespace acos::ui {

class LayoutNode {
public:
    LayoutNode() : m_size{0, 0}, m_position{0, 0} {}
    virtual ~LayoutNode() = default;

    virtual Size perform_layout(UIContext* ctx, Constraints constraints) = 0;

    Size size() const { return m_size; }
    Position position() const { return m_position; }
    void set_position(Position pos) { m_position = pos; }

protected:
    Size m_size;
    Position m_position;
};

} // namespace acos::ui
