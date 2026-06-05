#include "toast.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Toast::Toast() {
    m_rect = {0, 0, 100, 100};
}

Toast::~Toast() {}

Ref<RenderObject> Toast::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
