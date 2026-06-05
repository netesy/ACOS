#include "progressbar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ProgressBar::ProgressBar() {
    m_rect = {0, 0, 100, 100};
}

ProgressBar::~ProgressBar() {}

Ref<RenderObject> ProgressBar::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
