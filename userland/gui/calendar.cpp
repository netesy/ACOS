#include "calendar.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Calendar::Calendar() : m_year(2026), m_month(6), m_selected_day(2) {
    m_rect.w = 200;
    m_rect.h = 220;
}


Ref<RenderObject> Calendar::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
