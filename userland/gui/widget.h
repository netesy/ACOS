#pragma once
#include <acos/types.h>
#include <kernel/input/input_device.h>
#include <kernel/graphics/renderer.h>
#include "core/ref.h"
#include "core/vector.h"
#include "core/layout_types.h"
#include "core/style.h"

namespace acos::gui {

struct Event;
class RenderObject;

struct Rect {
    i32 x, y, w, h;
    bool contains(i32 px, i32 py) const {
        return px >= x && px < x + w && py >= y && py < y + h;
    }
};

enum class WidgetState {
    Normal,
    Hovered,
    Pressed,
    Focused,
    Disabled
};

enum class WidgetFlags {
    Visible = 1 << 0,
    Enabled = 1 << 1,
    Focusable = 1 << 2,
    Clickable = 1 << 3,
    LayoutDirty = 1 << 4,
    PaintDirty = 1 << 5
};

class Widget {
public:
    Widget();
    virtual ~Widget();

    virtual void draw(acos::graphics::Renderer* renderer) = 0;
    virtual void handle_event(const acos::input::InputEvent& event);
    virtual void handle_event(Event& event);
    virtual void on_event(Event& event);
    virtual Size layout(BoxConstraints constraints);
    virtual void update(u64 delta_ms);

    virtual Ref<RenderObject> create_render_object() = 0;
    virtual void update_render_object(Ref<RenderObject> render_object);

    void set_position(i32 x, i32 y) { m_rect.x = x; m_rect.y = y; }
    void set_size(i32 w, i32 h) { m_rect.w = w; m_rect.h = h; }
    void set_rect(const Rect& r) { m_rect = r; }
    Rect rect() const { return m_rect; }

    void set_parent(Ref<Widget> parent) { m_parent = parent; }
    Ref<Widget> parent() const { return m_parent; }
    void add_child(Ref<Widget> child);
    void remove_child(Ref<Widget> child);
    const Vector<Ref<Widget>>& children() const { return m_children; }

    Ref<Widget> self();

    // Fluent Modifiers
    Widget& background(u32 color);
    Widget& radius(u32 r);
    Widget& padding(u32 p);
    Widget& elevation(u32 e);

    bool is_visible() const { return m_flags & (u32)WidgetFlags::Visible; }
    void set_visible(bool v);
    
    bool is_enabled() const { return m_flags & (u32)WidgetFlags::Enabled; }
    void set_enabled(bool e);
    
    bool is_focused() const { return m_state == WidgetState::Focused; }
    void set_focused(bool f);
    
    bool is_focusable() const { return m_flags & (u32)WidgetFlags::Focusable; }

    bool is_layout_dirty() const { return m_flags & (u32)WidgetFlags::LayoutDirty; }
    void set_layout_dirty();
    void clear_layout_dirty() { m_flags &= ~(u32)WidgetFlags::LayoutDirty; }

    bool is_paint_dirty() const { return m_flags & (u32)WidgetFlags::PaintDirty; }
    void set_paint_dirty();

    WidgetState state() const { return m_state; }
    void set_state(WidgetState s) { m_state = s; }

    void set_elevation(u32 elevation) { m_style.elevation = elevation; }
    u32 elevation() const { return m_style.elevation; }

    virtual bool hit_test(i32 x, i32 y) const { return m_rect.contains(x, y); }

protected:
    Rect m_rect;
    Ref<Widget> m_parent;
    Vector<Ref<Widget>> m_children;
    u32 m_flags;
    WidgetState m_state;
    Style m_style;

    void draw_shadow(acos::graphics::Renderer* renderer);
};

} // namespace acos::gui
