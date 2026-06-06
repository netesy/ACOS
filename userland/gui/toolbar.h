#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class ToolBar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    ToolBar();
    virtual ~ToolBar();
};

} // namespace acos::gui::widgets
