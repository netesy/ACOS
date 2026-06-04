#pragma once
#include "widget.h"

namespace acos::gui {

class CheckBox : public Widget {
public:
    CheckBox(const char* label = nullptr);
    virtual ~CheckBox();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
    void on_event(Event& event) override;

    bool checked() const { return m_checked; }
    void set_checked(bool checked) { m_checked = checked; set_paint_dirty(); }

    // Fluent API
    CheckBox& label(const char* l) { m_label = l; set_layout_dirty(); return *this; }
    CheckBox& checked(bool c) { set_checked(c); return *this; }

private:
    const char* m_label;
    bool m_checked;
};

} // namespace acos::gui
