#pragma once
#include "widget.h"

namespace acos::gui {

class ToolBar : public Widget {
public:
    ToolBar();
    void draw(acos::graphics::Renderer* renderer) override;
};

} // namespace acos::gui
