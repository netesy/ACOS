#include "terminal.h"
#include <userland/gui/core/context.h>

namespace acos::apps {

Terminal::Terminal() : gui::WindowWidget("Terminal", 50, 50, 620, 420) {
    auto& region = gui::UIContext::get().region();

    m_view = region.alloc<TerminalView>();
    m_view->set_position(10, 40);
    m_view->set_size(600, 360);
    add_child(m_view.static_cast_to<gui::Widget>());
}

Terminal::~Terminal() {}

} // namespace acos::apps
