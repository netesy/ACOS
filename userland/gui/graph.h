#pragma once
#include "widget.h"

namespace acos::gui {

class Graph : public Widget {
public:
    Graph();
    void draw(acos::graphics::Renderer* renderer) override;
    void add_value(float val);

private:
    float m_data[64];
    u32 m_count;
};

} // namespace acos::gui
