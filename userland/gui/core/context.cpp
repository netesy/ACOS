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
    if (m_root) {
        // Sync widget tree to render tree
        sync_render_tree(m_root, m_root_render_object);
    }

    if (m_root_render_object) {
        m_root_render_object->paint(renderer);
    }
}

void UIContext::sync_render_tree(Ref<Widget> widget, Ref<RenderObject>& render_object) {
    if (!widget) return;

    if (!render_object) {
        render_object = widget->create_render_object();
    }

    if (render_object) {
        widget->update_render_object(render_object);

        const auto& widget_children = widget->children();
        const auto& ro_children = render_object->children();

        bool structure_changed = widget_children.size() != ro_children.size();
        // For now, if sizes don't match, we clear and rebuild
        if (structure_changed) {
            render_object->clear_children();
            for (u32 i = 0; i < widget_children.size(); i++) {
                Ref<RenderObject> child_ro;
                sync_render_tree(widget_children[i], child_ro);
                if (child_ro) render_object->add_child(child_ro);
            }
        } else {
            for (u32 i = 0; i < widget_children.size(); i++) {
                Ref<RenderObject> child_ro = ro_children[i];
                sync_render_tree(widget_children[i], child_ro);
            }
        }
    }
}

} // namespace acos::gui
