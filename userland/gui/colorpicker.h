#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui::widgets {

class ColorPicker : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    ColorPicker();
    virtual ~ColorPicker();

    u32 selected_color() const { return m_color; }
    Signal<u32> on_color_changed;

private:
    u32 m_color;
};

} // namespace acos::gui::widgets
