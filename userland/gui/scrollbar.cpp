#include "scrollbar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ScrollBar::ScrollBar() {
    m_rect = {0, 0, 100, 100};
}

ScrollBar::~ScrollBar() {}

Ref<RenderObject> ScrollBar::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
