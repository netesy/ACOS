#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui {

class Separator : public Widget {
public:
    Separator(Orientation orient = Orientation::Horizontal);
    void draw(acos::graphics::Renderer* renderer) override;

private:
    Orientation m_orientation;
};

} // namespace acos::gui
