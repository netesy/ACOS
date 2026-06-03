#pragma once
#include "widget.h"

namespace acos::gui {

class Tooltip : public Widget {
public:
    Tooltip();
    void draw(acos::graphics::Renderer* renderer) override;
    void set_text(const char* text) { m_text = text; }

private:
    const char* m_text;
};

} // namespace acos::gui
