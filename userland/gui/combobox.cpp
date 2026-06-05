#include "combobox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ComboBox::ComboBox() {
    m_rect = {0, 0, 100, 100};
}

ComboBox::~ComboBox() {}

Ref<RenderObject> ComboBox::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
