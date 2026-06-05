#include "splitter.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

Splitter::Splitter(Orientation orient) : m_orient(orient), m_first(nullptr), m_second(nullptr), m_ratio(0.5f), m_dragging(false) {}

void Splitter::set_widgets(Widget* first, Widget* second) {
    m_first = first;
    m_second = second;
    if (first) first->set_parent(this);
    if (second) second->set_parent(this);
}

void Splitter::set_split_ratio(float ratio) {
    m_ratio = ratio;
    if (m_ratio < 0.05f) m_ratio = 0.05f;
    if (m_ratio > 0.95f) m_ratio = 0.95f;
}



Ref<RenderObject> Splitter::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
