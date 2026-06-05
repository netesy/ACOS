#include "graph.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Graph::Graph() {
    m_rect = {0, 0, 100, 100};
}

Graph::~Graph() {}

Ref<RenderObject> Graph::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
