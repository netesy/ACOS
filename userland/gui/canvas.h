#pragma once
#include "widget.h"

namespace acos::gui {

class Canvas : public Widget {
public:
    Canvas();
    virtual ~Canvas();

    void draw(acos::graphics::Renderer* renderer) override;

    // Function pointer for custom drawing
    void (*m_on_draw)(Canvas*, acos::graphics::Renderer*);
    void* m_user_data;
};

} // namespace acos::gui
