#include "imagewidget.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ImageWidget::ImageWidget() {
    m_rect = {0, 0, 100, 100};
}

ImageWidget::~ImageWidget() {}

Ref<RenderObject> ImageWidget::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
