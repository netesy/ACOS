#include "tooltip.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Tooltip::Tooltip() : m_text(nullptr) {
    m_rect = {0, 0, 100, 24};
}

Tooltip::~Tooltip() {}

Ref<RenderObject> Tooltip::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
