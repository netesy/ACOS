#include <acos/process.h>
#include <acos/runtime.h>
#include <services/display/window.h>

namespace acos::display {

Window::Window(WindowId id, u64 owner_pid, u32 x, u32 y, u32 width, u32 height)
    : m_id(id), m_owner_pid(owner_pid), m_x(x), m_y(y), m_width(width), m_height(height),
      m_z_order(0), m_state(WindowState::Normal), m_flags(WindowFlags::None),
      m_focused(false), m_surface_id(0) {}

} // namespace acos::display
