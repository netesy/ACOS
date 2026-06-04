#include "separator.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Separator::Separator(Orientation orient) : m_orientation(orient) {
    if (m_orientation == Orientation::Horizontal) {
        m_rect.h = 1;
        m_rect.w = 100;
    } else {
        m_rect.w = 1;
        m_rect.h = 100;
    }
}


Ref<RenderObject> Separator::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
