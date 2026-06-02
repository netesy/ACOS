#pragma once
#include "widget.h"

namespace acos::gui {

class Panel : public Widget {
public:
    Panel();
    virtual ~Panel();

    void draw(acos::graphics::Renderer* renderer) override;

    void set_background_color(u32 color) { m_bg_color = color; }
    void set_glass(bool glass) { m_is_glass = glass; }

private:
    u32 m_bg_color;
    bool m_is_glass;
};

} // namespace acos::gui
