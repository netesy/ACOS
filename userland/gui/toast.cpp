#include <acos/process.h>
#include <acos/runtime.h>
#include "toast.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Toast::Toast(const char* message) : m_message(message), m_timer(0), m_duration(3000), m_alpha(0) {
    m_rect = {0, 0, 200, 50};
}

Toast::~Toast() {}

void Toast::update(::acos::u64 delta_ms) {
    (void)delta_ms;
}

void Toast::show(::acos::u32 duration_ms) {
    m_duration = duration_ms;
}

Ref<RenderObject> Toast::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
