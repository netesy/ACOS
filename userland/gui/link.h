#pragma once
#include "label.h"

namespace acos::gui::widgets {

class Link : public Label {
public:
    Ref<RenderObject> create_render_object() override;
    Link(const char* text);
    virtual ~Link();
};

} // namespace acos::gui::widgets
