#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui {

class MenuItem : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    MenuItem(const char* label = nullptr);

    Signal<> on_triggered;

private:
    const char* m_label;
};

} // namespace acos::gui
