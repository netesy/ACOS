#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class StackWidget : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    StackWidget();
    virtual ~StackWidget();

    void add_widget(Widget* widget);
    void set_current_index(::acos::u32 index);
    ::acos::u32 current_index() const { return m_current_index; }

private:
    [[maybe_unused]] Widget* m_pages[16];
    ::acos::u32 m_count;
    ::acos::u32 m_current_index;
};

} // namespace acos::gui::widgets
