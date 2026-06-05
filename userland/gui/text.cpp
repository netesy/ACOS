#include "text.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Text::Text() {
    m_rect = {0, 0, 100, 100};
}

Text::~Text() {}

Ref<RenderObject> Text::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
