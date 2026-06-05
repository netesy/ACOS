#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Badge : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Badge(const char* text = nullptr);
    void set_text(const char* text) { m_text = text; }

private:
    const char* m_text;
};

} // namespace acos::gui::widgets
