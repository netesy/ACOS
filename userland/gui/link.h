#pragma once
#include "label.h"
#include "signal.h"

namespace acos::gui {

class Link : public Label {
public:
    Ref<RenderObject> create_render_object() override;
    Link(const char* text);

    Signal<> on_clicked;
};

} // namespace acos::gui
