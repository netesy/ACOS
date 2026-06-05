#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui::widgets {

class Splitter : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Splitter(Orientation orient = Orientation::Horizontal);

    void set_widgets(Widget* first, Widget* second);
    void set_split_ratio(float ratio);

private:
    Orientation m_orient;
    Widget* m_first;
    Widget* m_second;
    float m_ratio;
    bool m_dragging;
};

} // namespace acos::gui::widgets
