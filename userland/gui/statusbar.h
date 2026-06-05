#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class StatusBar : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    StatusBar();
    void set_text(const char* text) { m_text = text; }

private:
    const char* m_text;
};

} // namespace acos::gui::widgets
