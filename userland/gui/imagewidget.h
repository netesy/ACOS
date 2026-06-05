#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class ImageWidget : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    ImageWidget();
    void set_image(u32* data, u32 w, u32 h) { m_data = data; m_img_w = w; m_img_h = h; }

private:
    u32* m_data;
    u32 m_img_w, m_img_h;
};

} // namespace acos::gui::widgets
