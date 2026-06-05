#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Graph : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Graph();
    void add_value(float val);

private:
    float m_data[64];
    u32 m_count;
};

} // namespace acos::gui::widgets
