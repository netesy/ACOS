#include "groupbox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

GroupBox::GroupBox(const char* title) : m_title(title) {
    m_rect = {0, 0, 100, 100};
}


Ref<RenderObject> Groupbox::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> GroupBox::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
