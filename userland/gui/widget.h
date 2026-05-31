#pragma once
#include <acos/types.h>
#include <kernel/input/input_device.h>

namespace acos::gui {

struct Rect {
    i32 x, y, w, h;
    bool contains(i32 px, i32 py) const {
        return px >= x && px < x + w && py >= y && py < y + h;
    }
};

class Widget {
public:
    Widget();
    virtual ~Widget();

    virtual void draw(u32* buffer, u32 pitch) = 0;
    virtual void handle_event(const acos::input::InputEvent& event);

    void set_position(i32 x, i32 y) { m_rect.x = x; m_rect.y = y; }
    void set_size(i32 w, i32 h) { m_rect.w = w; m_rect.h = h; }
    Rect rect() const { return m_rect; }

    void set_parent(Widget* parent) { m_parent = parent; }
    Widget* parent() const { return m_parent; }

    bool is_visible() const { return m_visible; }
    void set_visible(bool v) { m_visible = v; }

protected:
    Rect m_rect;
    Widget* m_parent;
    bool m_visible;
};

} // namespace acos::gui
