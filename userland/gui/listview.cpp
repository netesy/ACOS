#include "listview.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ListView::ListView() {
    m_rect = {0, 0, 100, 100};
}

ListView::~ListView() {}

Ref<RenderObject> ListView::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
