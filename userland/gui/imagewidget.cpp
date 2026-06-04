#include "imagewidget.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ImageWidget::ImageWidget() : m_data(nullptr), m_img_w(0), m_img_h(0) {}


Ref<RenderObject> ImageWidget::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
