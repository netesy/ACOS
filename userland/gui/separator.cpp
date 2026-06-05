#include "separator.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Separator::Separator() {
    m_rect = {0, 0, 100, 100};
}

Separator::~Separator() {}

Ref<RenderObject> Separator::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
