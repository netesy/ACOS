#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Badge : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
    Badge(const char* text = nullptr);
    virtual ~Badge();
    void set_text(const char* text) { m_text = text; }

private:
    [[maybe_unused]] const char* m_text;
};

} // namespace acos::gui::widgets
