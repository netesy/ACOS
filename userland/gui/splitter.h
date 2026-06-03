#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui {

class Splitter : public Widget {
public:
    Splitter(Orientation orient = Orientation::Horizontal);
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;

    void set_widgets(Widget* first, Widget* second);
    void set_split_ratio(float ratio);

private:
    Orientation m_orient;
    Widget* m_first;
    Widget* m_second;
    float m_ratio;
    bool m_dragging;
};

} // namespace acos::gui
