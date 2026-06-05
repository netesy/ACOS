#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Switch : public Widget {
public:
    Switch(const char* label = nullptr);
    virtual ~Switch();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
    void on_event(Event& event) override;

    bool on() const { return m_on; }
    void set_on(bool on) { m_on = on; set_paint_dirty(); }

    // Internal Fluent API
    Switch& label(const char* l) { m_label = l; set_layout_dirty(); return *this; }
    Switch& on(bool o) { set_on(o); return *this; }

private:
    const char* m_label;
    bool m_on;
};

} // namespace acos::gui::widgets
