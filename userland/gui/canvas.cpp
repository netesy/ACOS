#include "canvas.h"

namespace acos::gui {

Canvas::Canvas() : m_on_draw(nullptr), m_user_data(nullptr) {}
Canvas::~Canvas() {}


Ref<RenderObject> Canvas::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui
