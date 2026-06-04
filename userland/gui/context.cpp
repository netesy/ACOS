#include "context.h"
#include "focus_manager.h"
#include "animation.h"
#include "theme.h"
#include "widget.h"
#include "layout_node.h"
#include "render_object.h"

namespace acos::ui {

UIContext::UIContext(usize region_size)
    : m_region(region_size),
      m_pool(region_size / 64)
{
    m_focus_manager = new FocusManager();
    m_animation_manager = new AnimationManager();
}

void UIContext::update(u64 now) {
    m_animation_manager->update(this, now);
}

void UIContext::process_event(UIEvent& event) {
    m_dispatcher.dispatch(this, m_render_root, event);
}

void UIContext::perform_layout(Constraints constraints) {
    if (!m_layout_root.is_null()) {
        m_layout_root.get(this)->perform_layout(this, constraints);
    }
}

void UIContext::paint(acos::graphics::Renderer* renderer) {
    if (!m_render_root.is_null()) {
        m_render_root.get(this)->paint(this, renderer, {0, 0});
    }
}

void UIContext::build_tree(Ref<Widget> root) {
    if (root.is_null()) return;

    Widget* root_ptr = root.get(this);
    m_layout_root = root_ptr->create_layout_node(this);
    m_render_root = root_ptr->create_render_object(this);

    root_ptr->set_layout_node(m_layout_root);
    root_ptr->set_render_object(m_render_root);

    build_recursive(root, m_layout_root, m_render_root);
}

void UIContext::build_recursive(Ref<Widget> widget, Ref<LayoutNode> parent_layout, Ref<RenderObject> parent_render) {
    Widget* w_ptr = widget.get(this);
    w_ptr->build(this);

    for (auto& child_ref : w_ptr->children()) {
        Widget* c_ptr = child_ref.get(this);

        Ref<LayoutNode> c_layout = c_ptr->create_layout_node(this);
        Ref<RenderObject> c_render = c_ptr->create_render_object(this);

        c_ptr->set_layout_node(c_layout);
        c_ptr->set_render_object(c_render);

        if (!c_layout.is_null() && !parent_layout.is_null()) {
            parent_layout.get(this)->add_child(this, parent_layout, c_layout);
        }

        if (!c_render.is_null() && !parent_render.is_null()) {
            parent_render.get(this)->add_child(this, parent_render, c_render);
        }

        build_recursive(child_ref, c_layout, c_render);
    }
}

void UIContext::rebuild_dirty_widgets(Ref<Widget> root) {
    if (root.is_null()) return;
    Widget* w_ptr = root.get(this);
    if (w_ptr->is_dirty()) {
        w_ptr->build(this);
        w_ptr->clear_dirty();

        Ref<LayoutNode> ln = w_ptr->layout_node();
        if (!ln.is_null()) w_ptr->update_layout_node(this, ln);

        Ref<RenderObject> ro = w_ptr->render_object();
        if (!ro.is_null()) w_ptr->update_render_object(this, ro);
    }

    for (auto& child_ref : w_ptr->children()) {
        rebuild_dirty_widgets(child_ref);
    }
}

Theme& UIContext::theme() {
    static Theme default_theme;
    return default_theme;
}

} // namespace acos::ui
