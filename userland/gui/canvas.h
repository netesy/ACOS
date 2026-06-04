#pragma once
#include "widget.h"

namespace acos::gui {

class Canvas : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Canvas();
    virtual ~Canvas();


    // Function pointer for custom drawing
    void (*m_on_draw)(Canvas*, acos::graphics::Renderer*);
    void* m_user_data;
};

} // namespace acos::gui
