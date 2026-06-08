#include "context.h"
#include "style.h"
#include "../widget.h"

namespace acos::gui {

// Screen dimensions stored during paint for fixed-position resolution
static ::acos::i32 g_screen_w = 0;
static ::acos::i32 g_screen_h = 0;

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

// Resolve fixed/absolute render objects after normal flow layout
// static void resolve_positioned(Ref<RenderObject> ro) {
//     if (!ro) return;

//     // Recurse children first
//     const auto& children = ro->children();
//     for (::acos::u32 i = 0; i < children.size(); i++) {
//         resolve_positioned(children[i]);
//     }
// }

void UIContext::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;

    g_screen_w = (::acos::i32)renderer->width();
    g_screen_h = (::acos::i32)renderer->height();

    if (m_root) {
        sync_render_tree(m_root, m_root_render_object);
    }

    if (m_root_render_object) {
        m_root_render_object->perform_layout(BoxConstraints::tight(g_screen_w, g_screen_h));

        // Second pass: apply fixed/absolute positioning overrides
        apply_positioned_layout(m_root, m_root_render_object, g_screen_w, g_screen_h);

        if (m_compositor) {
            // m_compositor->composite();
        } else {
            m_root_render_object->paint(renderer);
        }
    }
}

void UIContext::apply_positioned_layout(Ref<Widget> widget, Ref<RenderObject> render_object,
                                         ::acos::i32 screen_w, ::acos::i32 screen_h) {
    if (!widget || !render_object) return;

    const acos::gui::Style& s = widget->style();

    if (s.position == Position::Fixed) {
        // Compute size from preferred or fallback to current
        ::acos::i32 w = (s.preferred_w > 0) ? s.preferred_w : render_object->rect().w;
        ::acos::i32 h = (s.preferred_h > 0) ? s.preferred_h : render_object->rect().h;

        ::acos::i32 x = render_object->rect().x;
        ::acos::i32 y = render_object->rect().y;

        // Horizontal positioning
        if (s.anchor_left >= 0 && s.anchor_right >= 0) {
            // Stretch horizontally between left and right
            x = s.anchor_left;
            // Note: w will be overridden by the stretch; apply in layout constraints
        } else if (s.anchor_left >= 0) {
            // Pin to left
            x = s.anchor_left;
        } else if (s.anchor_right >= 0) {
            // Pin to right
            x = screen_w - w - s.anchor_right;
        } else {
            // Center horizontally (both left and right are -1)
            x = (screen_w - w) / 2;
        }

        // Vertical positioning
        if (s.anchor_top >= 0 && s.anchor_bottom >= 0) {
            // Stretch vertically between top and bottom
            y = s.anchor_top;
            // Note: h will be overridden by the stretch; apply in layout constraints
        } else if (s.anchor_top >= 0) {
            // Pin to top
            y = s.anchor_top;
        } else if (s.anchor_bottom >= 0) {
            // Pin to bottom
            y = screen_h - h - s.anchor_bottom;
        } else {
            // Center vertically (both top and bottom are -1)
            y = (screen_h - h) / 2;
        }

        render_object->set_rect({x, y, w, h});

        // Re-layout children within new bounds
        render_object->perform_layout(BoxConstraints::tight(w, h));

    } else if (s.position == Position::Absolute) {
        // Relative to parent container (already laid out)
        // anchor values are relative to parent origin
        Ref<RenderObject> parent = render_object->parent();
        ::acos::i32 px = parent ? parent->rect().x : 0;
        ::acos::i32 py = parent ? parent->rect().y : 0;
        ::acos::i32 pw = parent ? parent->rect().w : screen_w;
        ::acos::i32 ph = parent ? parent->rect().h : screen_h;

        ::acos::i32 w = (s.preferred_w > 0) ? s.preferred_w : render_object->rect().w;
        ::acos::i32 h = (s.preferred_h > 0) ? s.preferred_h : render_object->rect().h;
        ::acos::i32 x = px;
        ::acos::i32 y = py;

        if (s.anchor_left >= 0)   x = px + s.anchor_left;
        if (s.anchor_right >= 0)  x = px + pw - w - s.anchor_right;
        if (s.anchor_top >= 0)    y = py + s.anchor_top;
        if (s.anchor_bottom >= 0) y = py + ph - h - s.anchor_bottom;

        render_object->set_rect({x, y, w, h});
        render_object->perform_layout(BoxConstraints::tight(w, h));

    } else if (s.position == Position::Relative) {
        // Offset from normal-flow position
        Rect r = render_object->rect();
        ::acos::i32 dx = (s.anchor_left >= 0) ? s.anchor_left : (s.anchor_right >= 0 ? -s.anchor_right : 0);
        ::acos::i32 dy = (s.anchor_top >= 0)  ? s.anchor_top  : (s.anchor_bottom >= 0 ? -s.anchor_bottom : 0);
        render_object->set_rect({r.x + dx, r.y + dy, r.w, r.h});
    }

    // Recurse into widget children
    const auto& widget_children = widget->children();
    const auto& ro_children = render_object->children();
    ::acos::u32 count = widget_children.size() < ro_children.size() ? widget_children.size() : ro_children.size();
    for (::acos::u32 i = 0; i < count; i++) {
        apply_positioned_layout(widget_children[i], ro_children[i], screen_w, screen_h);
    }
}

void UIContext::update(::acos::u64 delta_ms) {
    m_animation_controller.tick(delta_ms);
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
        if (structure_changed) {
            render_object->clear_children();
            for (::acos::u32 i = 0; i < widget_children.size(); i++) {
                Ref<RenderObject> child_ro;
                sync_render_tree(widget_children[i], child_ro);
                if (child_ro) render_object->add_child(child_ro);
            }
        } else {
            for (::acos::u32 i = 0; i < widget_children.size(); i++) {
                Ref<RenderObject> child_ro = ro_children[i];
                sync_render_tree(widget_children[i], child_ro);
            }
        }
    }
}

} // namespace acos::gui
