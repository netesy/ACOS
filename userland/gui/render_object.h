#pragma once
#include "geometry.h"
#include "ref.h"
#include "event.h"
#include "kernel/graphics/renderer.h"

namespace acos::ui {

class UIContext;

class RenderObject {
public:
    RenderObject();
    virtual ~RenderObject() = default;
    virtual void paint(UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) = 0;
    virtual bool hit_test(UIContext* ctx, Position point, Position offset);
    virtual void handle_event([[maybe_unused]] UIContext* ctx, [[maybe_unused]] UIEvent& event, [[maybe_unused]] EventPhase phase) {}

    Size size() const { return m_size; }
    void set_size(Size s) { m_size = s; }

    Position position() const { return m_position; }
    void set_position(Position p) { m_position = p; }

    Ref<RenderObject> parent() const { return m_parent; }
    Ref<RenderObject> first_child() const { return m_first_child; }
    Ref<RenderObject> next_sibling() const { return m_next_sibling; }

    void add_child(UIContext* ctx, Ref<RenderObject> self, Ref<RenderObject> child);

protected:
    Size m_size; Position m_position;
    Ref<RenderObject> m_parent, m_first_child, m_last_child, m_next_sibling;
};

} // namespace acos::ui
