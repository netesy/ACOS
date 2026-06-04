#pragma once
#include "button.h"

namespace acos::gui {

class ToolButton : public Button {
public:
    Ref<RenderObject> create_render_object() override;
    ToolButton(const char* label = nullptr);
};

} // namespace acos::gui
