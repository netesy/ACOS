#pragma once
#include <acos/types.h>
#include <kernel/input/input_device.h>
#include <acos/graphics.h>
#include "core/ref.h"
#include "core/vector.h"
#include "core/layout_types.h"
#include "core/style.h"
#include "core/render_object.h"
namespace acos::gui {

using ::acos::Vector;

struct Event;

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

    virtual void handle_event(Event& event);
    virtual void on_event(Event& event);
    virtual Size layout(BoxConstraints constraints);
    virtual void update(::acos::u64 delta_ms);

    virtual Ref<RenderObject> create_render_object() = 0;
    virtual void update_render_object(Ref<RenderObject> render_object);

    void set_position(::acos::i32 x, ::acos::i32 y) { m_rect.x = x; m_rect.y = y; }
    void set_size(::acos::i32 w, ::acos::i32 h) { m_rect.w = w; m_rect.h = h; }
    void set_rect(const Rect& r) { m_rect = r; }
    Rect rect() const { return m_rect; }

    void set_parent(Ref<Widget> parent) { m_parent = parent; }
    Ref<Widget> parent() const { return m_parent; }
    virtual void add_child(Ref<Widget> child);
    virtual void remove_child(Ref<Widget> child);
    const Vector<Ref<Widget>>& children() const { return m_children; }

    Ref<Widget> self();

    // Fluent Modifiers
    Widget& background(::acos::u32 color);
    Widget& radius(::acos::u32 r);
    Widget& padding(::acos::u32 p);
    Widget& padding(::acos::u32 top, ::acos::u32 right, ::acos::u32 bottom, ::acos::u32 left);
    Widget& margin(::acos::u32 m);
    Widget& margin(::acos::u32 top, ::acos::u32 right, ::acos::u32 bottom, ::acos::u32 left);
    Widget& preferred_size(::acos::i32 w, ::acos::i32 h);
    Widget& preferred_width(::acos::i32 w);
    Widget& preferred_height(::acos::i32 h);
    Widget& flex_grow(::acos::u32 factor);
    Widget& elevation(::acos::u32 e);
    Widget& opacity(float o);
    // Positioning
    Widget& position(Position pos);
    Widget& anchor_top(::acos::i32 v);
    Widget& anchor_right(::acos::i32 v);
    Widget& anchor_bottom(::acos::i32 v);
    Widget& anchor_left(::acos::i32 v);
    // Shorthand: fixed position pinned to screen edges
    Widget& fixed(::acos::i32 top = -1, ::acos::i32 right = -1, ::acos::i32 bottom = -1, ::acos::i32 left = -1);

    bool is_visible() const { return m_flags & (::acos::u32)WidgetFlags::Visible; }
    void set_visible(bool v);
    
    bool is_enabled() const { return m_flags & (::acos::u32)WidgetFlags::Enabled; }
    void set_enabled(bool e);
    
    bool is_focused() const { return m_state == WidgetState::Focused; }
    void set_focused(bool f);
    
    bool is_focusable() const { return m_flags & (::acos::u32)WidgetFlags::Focusable; }

    bool is_layout_dirty() const { return m_flags & (::acos::u32)WidgetFlags::LayoutDirty; }
    void set_layout_dirty();
    void clear_layout_dirty() { m_flags &= ~(::acos::u32)WidgetFlags::LayoutDirty; }

    bool is_paint_dirty() const { return m_flags & (::acos::u32)WidgetFlags::PaintDirty; }
    void set_paint_dirty();

    WidgetState state() const { return m_state; }
    void set_state(WidgetState s) { m_state = s; }

    void set_elevation(::acos::u32 elevation) { m_style.elevation = elevation; }
    ::acos::u32 elevation() const { return m_style.elevation; }

    void set_background_color(::acos::u32 color) { m_style.background_color = color; set_paint_dirty(); }
    void set_border_color(::acos::u32 color) { m_style.border_color = color; set_paint_dirty(); }
    void set_border_width(::acos::u32 width) { m_style.border_width = width; set_layout_dirty(); }
    void set_foreground_color(::acos::u32 color) { m_style.foreground_color = color; set_paint_dirty(); }

    bool hit_test(::acos::i32 x, ::acos::i32 y) const { return m_rect.contains(x, y); }

    // Style read access
    const Style& style() const { return m_style; }
    Style& style() { return m_style; }

protected:
    Rect m_rect;
    Ref<Widget> m_parent;
    Vector<Ref<Widget>> m_children;
    ::acos::u32 m_flags;
    WidgetState m_state;
    Style m_style;

    void draw_shadow(::acos::graphics::Renderer* renderer);
};

} // namespace acos::gui
