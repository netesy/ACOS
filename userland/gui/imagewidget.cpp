#include <acos/process.h>
#include <acos/runtime.h>
#include "imagewidget.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ImageWidget::ImageWidget() : m_data(nullptr), m_img_w(0), m_img_h(0) {
    m_rect = {0, 0, 100, 100};
}

ImageWidget::~ImageWidget() {}

Ref<RenderObject> ImageWidget::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
