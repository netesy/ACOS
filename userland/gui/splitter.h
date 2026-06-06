#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui::widgets {

class Splitter : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Splitter(Orientation orient = Orientation::Horizontal);
    virtual ~Splitter();

    void set_widgets(Widget* first, Widget* second);
    void set_split_ratio(float ratio);

private:
    [[maybe_unused]] Orientation m_orient;
    [[maybe_unused]] Widget* m_first;
    [[maybe_unused]] Widget* m_second;
    [[maybe_unused]] float m_ratio;
    [[maybe_unused]] bool m_dragging;
};

} // namespace acos::gui::widgets
