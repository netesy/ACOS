#include "graph.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

Graph::Graph() : m_count(0) {
    m_rect = {0, 0, 200, 100};
    for (int i = 0; i < 64; i++) m_data[i] = 0;
}

Graph::~Graph() {}

void Graph::add_value(float val) {
    if (m_count < 64) {
        m_data[m_count++] = val;
    } else {
        for (int i = 0; i < 63; i++) m_data[i] = m_data[i+1];
        m_data[63] = val;
    }
    set_paint_dirty();
}

Ref<RenderObject> Graph::create_render_object() {
    return UIContext::get().region().alloc<RenderGraph>();
}

void Graph::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rg = static_cast<RenderGraph*>(render_object.operator->());
    if (rg) {
        rg->set_data(m_data, m_count);
    }
}

} // namespace acos::gui::widgets
