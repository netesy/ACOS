#include "context.h"

namespace acos::gui {

UIContext* UIContext::s_instance = nullptr;

UIContext::UIContext() : m_main_region(2048) {
    if (!s_instance) s_instance = this;
}

UIContext::~UIContext() {
    if (s_instance == this) s_instance = nullptr;
}

UIContext& UIContext::get() {
    return *s_instance;
}

void UIContext::paint(acos::graphics::Renderer* renderer) {
    // In a real framework, we'd have a root RenderObject.
    // For now, we'll traverse the Widget tree and call draw,
    // as Phase 5 is still in transition.
    // Future: root_render_object->paint(renderer);
}

} // namespace acos::gui
