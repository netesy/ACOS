#pragma once
#include "widget.h"

namespace acos::gui {

class GroupBox : public Widget {
public:
    GroupBox(const char* title = nullptr);
    void draw(acos::graphics::Renderer* renderer) override;

private:
    const char* m_title;
};

} // namespace acos::gui
