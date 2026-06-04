#include "focus_manager.h"
#include "render_object.h"

namespace acos::ui {

FocusManager::FocusManager() : m_focused_node(Ref<RenderObject>::null()) {}

void FocusManager::set_focus(Ref<RenderObject> node) {
    m_focused_node = node;
    // In the future, send FocusIn/FocusOut events here
}

} // namespace acos::ui
