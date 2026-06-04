#include "graph.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

Graph::Graph() : m_count(0) {
    m_rect.w = 200;
    m_rect.h = 100;
    for(int i=0; i<64; i++) m_data[i] = 0;
}

void Graph::add_value(float val) {
    if (m_count < 64) m_data[m_count++] = val;
    else {
        for(int i=0; i<63; i++) m_data[i] = m_data[i+1];
        m_data[63] = val;
    }
}


Ref<RenderObject> Graph::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
