#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui::widgets {

class MenuItem : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    MenuItem(const char* label = nullptr);
    virtual ~MenuItem();

    Signal<> on_triggered;

private:
    [[maybe_unused]] const char* m_label;
};

} // namespace acos::gui::widgets
