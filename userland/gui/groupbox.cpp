#include "groupbox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

GroupBox::GroupBox(const char* title) : m_title(title) {
    m_rect = {0, 0, 100, 100};
}

GroupBox::~GroupBox() {}

Ref<RenderObject> GroupBox::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
