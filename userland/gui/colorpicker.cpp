#include "colorpicker.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

ColorPicker::ColorPicker() : m_color(0xFFFFFFFF) {
    m_rect.w = 150;
    m_rect.h = 100;
}



Ref<RenderObject> Colorpicker::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ColorPicker::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
