#pragma once
#include "widget.h"

namespace acos::gui {

class StatusBar : public Widget {
public:
    StatusBar();
    void draw(acos::graphics::Renderer* renderer) override;
    void set_text(const char* text) { m_text = text; }

private:
    const char* m_text;
};

} // namespace acos::gui
