#pragma once
#include <acos/types.h>
#include <kernel/input/input_device.h>
#include <kernel/graphics/renderer.h>

namespace acos::gui {

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
    Visible = 1,
    Enabled = 2,
    Focusable = 4,
    Clickable = 8
};

class Widget {
public:
    Widget();
    virtual ~Widget();

    virtual void draw(acos::graphics::Renderer* renderer) = 0;
    virtual void handle_event(const acos::input::InputEvent& event);
    virtual void update(u64 delta_ms);

    void set_position(i32 x, i32 y) { m_rect.x = x; m_rect.y = y; }
    void set_size(i32 w, i32 h) { m_rect.w = w; m_rect.h = h; }
    void set_rect(const Rect& r) { m_rect = r; }
    Rect rect() const { return m_rect; }

    void set_parent(Widget* parent) { m_parent = parent; }
    Widget* parent() const { return m_parent; }
    void add_child(Widget* child);
    void remove_child(Widget* child);

    bool is_visible() const { return m_flags & (u32)WidgetFlags::Visible; }
    void set_visible(bool v);
    
    bool is_enabled() const { return m_flags & (u32)WidgetFlags::Enabled; }
    void set_enabled(bool e);
    
    bool is_focused() const { return m_state == WidgetState::Focused; }
    void set_focused(bool f);
    
    WidgetState state() const { return m_state; }
    void set_state(WidgetState s) { m_state = s; }

    bool hit_test(i32 x, i32 y) const { return m_rect.contains(x, y); }

protected:
    Rect m_rect;
    Widget* m_parent;
    Widget* m_children[32]; // Increased capacity
    u32 m_child_count;
    u32 m_flags;
    WidgetState m_state;
};

} // namespace acos::gui
