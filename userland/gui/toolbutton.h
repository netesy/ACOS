#pragma once
#include "button.h"

namespace acos::gui {

class ToolButton : public Button {
public:
    ToolButton(const char* label = nullptr);
    void draw(acos::graphics::Renderer* renderer) override;
};

} // namespace acos::gui
