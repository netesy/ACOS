#include <acos/process.h>
#include <acos/runtime.h>
#include "statusbar.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

StatusBar::StatusBar() : m_text(nullptr) {
    m_rect = {0, 0, 100, 24};
}

StatusBar::~StatusBar() {}

Ref<RenderObject> StatusBar::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
