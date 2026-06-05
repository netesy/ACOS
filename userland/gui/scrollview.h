#pragma once
#include "widget.h"
#include "scrollbar.h"

namespace acos::gui::widgets {

class ScrollView : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    ScrollView();
    virtual ~ScrollView();


    void add_content(Widget* widget);

private:
    ScrollBar m_v_scroll;
    Widget* m_content;
};

} // namespace acos::gui::widgets
