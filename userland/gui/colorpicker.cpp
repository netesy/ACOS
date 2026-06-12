#include <acos/process.h>
#include <acos/runtime.h>
#include "colorpicker.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ColorPicker::ColorPicker() {
    m_rect = {0, 0, 100, 100};
}

ColorPicker::~ColorPicker() {}

Ref<RenderObject> ColorPicker::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
