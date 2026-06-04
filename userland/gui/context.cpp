#include "context.h"
#include "widget.h"
#include "focus_manager.h"
#include "animation.h"
#include "theme.h"

namespace acos::ui {

UIContext::UIContext(usize region_size) : m_region(region_size), m_pool(4096) {
    m_focus_manager = m_region.make<FocusManager>();
    m_animation_manager = m_region.make<AnimationManager>();
}

Theme& UIContext::theme() { return Theme::instance(); }

void UIContext::process_event(UIEvent& event) {
    m_dispatcher.dispatch(this, m_render_root, event);
}

void UIContext::update(u64 now) {
    m_animation_manager->update(this, now);
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
    Widget* root_widget = root.get(this);
    root_widget->build(this);
    m_layout_root = root_widget->create_layout_node(this);
    m_render_root = root_widget->create_render_object(this);
    root_widget->set_layout_node(m_layout_root);
    root_widget->set_render_object(m_render_root);
    build_recursive(root, m_layout_root, m_render_root);
}

void UIContext::build_recursive(Ref<Widget> widget, Ref<LayoutNode> parent_layout, Ref<RenderObject> parent_render) {
    Widget* w = widget.get(this);
    w->build(this);
    auto node = w->children().head();
    while (node) {
        Ref<Widget> cw_ref = node->value;
        Widget* cw = cw_ref.get(this);
        Ref<LayoutNode> cl = cw->create_layout_node(this);
        Ref<RenderObject> cr = cw->create_render_object(this);
        cw->set_layout_node(cl);
        cw->set_render_object(cr);
        parent_layout.get(this)->add_child(this, parent_layout, cl);
        parent_render.get(this)->add_child(this, parent_render, cr);
        build_recursive(cw_ref, cl, cr);
        node = node->next;
    }
}

void UIContext::rebuild_dirty_widgets(Ref<Widget> root) {
    if (root.is_null()) return;
    Widget* w = root.get(this);
    if (w->is_dirty()) {
        w->update_layout_node(this, w->layout_node());
        w->update_render_object(this, w->render_object());
        w->clear_dirty();
    }
    auto node = w->children().head();
    while (node) {
        rebuild_dirty_widgets(node->value);
        node = node->next;
    }
}

} // namespace acos::ui
