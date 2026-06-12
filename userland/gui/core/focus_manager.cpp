#include <acos/process.h>
#include <acos/runtime.h>
#include "focus_manager.h"
#include "../widget.h"

namespace acos::gui {

void FocusManager::set_focus(Ref<Widget> widget) {
    if (m_focused == widget) return;

    if (m_focused) m_focused->set_focused(false);
    m_focused = widget;
    if (m_focused) m_focused->set_focused(true);
}

} // namespace acos::gui
