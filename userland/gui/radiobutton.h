#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class RadioButtonGroup;

class RadioButton : public Widget {
public:
    RadioButton(const char* label = nullptr);
    virtual ~RadioButton();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;
    void on_event(Event& event) override;

    bool selected() const { return m_selected; }
    void set_selected(bool selected);

    void set_group(RadioButtonGroup* group) { m_group = group; }

    // Internal Fluent API
    RadioButton& label(const char* l) { m_label = l; set_layout_dirty(); return *this; }
    RadioButton& selected(bool s) { set_selected(s); return *this; }

private:
    const char* m_label;
    bool m_selected;
    RadioButtonGroup* m_group;
};

class RadioButtonGroup {
public:
    RadioButtonGroup();
    void add_button(Ref<RadioButton> button);
    void select(Ref<RadioButton> selected_button);

private:
    Vector<Ref<RadioButton>> m_buttons;
};

} // namespace acos::gui::widgets
