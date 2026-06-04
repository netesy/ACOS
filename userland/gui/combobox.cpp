#include "combobox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ComboBox::ComboBox() : m_expanded(false), m_current_text("Select...") {
    m_rect.w = 150;
    m_rect.h = 28;
    m_popup.set_visible(false);
}

ComboBox::~ComboBox() {}

void ComboBox::add_item(const char* item) {
    m_popup.add_item(item);
}

const char* ComboBox::selected_item() const {
    return m_current_text;
}



Ref<RenderObject> Combobox::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ComboBox::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
