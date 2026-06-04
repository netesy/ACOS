#pragma once
#include "layout_node.h"

namespace acos::ui {

class LeafLayoutNode : public LayoutNode {
public:
    Size perform_layout([[maybe_unused]] UIContext* ctx, Constraints constraints) override {
        m_size = constraints.satisfy({0, 0});
        return m_size;
    }
};

} // namespace acos::ui
