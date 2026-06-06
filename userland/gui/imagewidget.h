#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class ImageWidget : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    ImageWidget();
    virtual ~ImageWidget();
    void set_image(::acos::u32* data, ::acos::u32 w, ::acos::u32 h) { m_data = data; m_img_w = w; m_img_h = h; }

private:
    ::acos::u32* m_data;
    ::acos::u32 m_img_w, m_img_h;
};

} // namespace acos::gui::widgets
