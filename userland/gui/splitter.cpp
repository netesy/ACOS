#include "splitter.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Splitter::Splitter(Orientation orient) : m_orient(orient), m_first(nullptr), m_second(nullptr), m_ratio(0.5f), m_dragging(false) {
    m_rect = {0, 0, 100, 100};
}

Splitter::~Splitter() {}

Ref<RenderObject> Splitter::create_render_object() {
    return Ref<RenderObject>();
}

void Splitter::set_widgets(Widget* first, Widget* second) {
    m_first = first;
    m_second = second;
}

void Splitter::set_split_ratio(float ratio) {
    m_ratio = ratio;
}

} // namespace acos::gui::widgets
