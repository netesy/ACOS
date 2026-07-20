#include <kernel/input/mouse_manager.h>
#include <kernel/input/input_manager.h>
#include <kernel/graphics/graphics_manager.h>

namespace acos::input {

using abi::InputType;
using abi::InputEvent;

i32 MouseManager::m_x = 0;
i32 MouseManager::m_y = 0;
u32 MouseManager::m_buttons = 0;

void MouseManager::init() {
    m_x = 100;
    m_y = 100;
    m_buttons = 0;
}

void MouseManager::handle_movement(i32 dx, i32 dy) {
    u32 max_w = 1024;
    u32 max_h = 768;
    auto* display = graphics::GraphicsManager::primary_display();
    if (display) {
        max_w = display->width();
        max_h = display->height();
    }

    m_x += dx;
    m_y += dy;

    if (m_x < 0) m_x = 0;
    if (m_x >= (i32)max_w) m_x = max_w - 1;
    if (m_y < 0) m_y = 0;
    if (m_y >= (i32)max_h) m_y = max_h - 1;

    InputEvent event;
    event.type = InputType::Mouse;
    event.code = (static_cast<u32>(m_x) << 16) | (static_cast<u32>(m_y) & 0xFFFF);
    event.value = m_buttons;
    event.flags = 0;

    InputManager::push_event(event);
}

void MouseManager::handle_button(u32 button, bool pressed) {
    if (pressed) {
        m_buttons |= (1 << button);
    } else {
        m_buttons &= ~(1 << button);
    }

    InputEvent event;
    event.type = InputType::Mouse;
    event.code = (static_cast<u32>(m_x) << 16) | (static_cast<u32>(m_y) & 0xFFFF);
    event.value = m_buttons;
    event.flags = 0;

    InputManager::push_event(event);
}

} // namespace acos::input
