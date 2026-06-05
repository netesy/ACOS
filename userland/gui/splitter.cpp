#include "splitter.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Splitter::Splitter() {
    m_rect = {0, 0, 100, 100};
}

Splitter::~Splitter() {}

Ref<RenderObject> Splitter::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
