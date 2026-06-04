#include "render_object.h"
#include "context.h"

namespace acos::gui {

Ref<RenderObject> RenderObject::self() {
    return UIContext::get().region().get_ref(this);
}

} // namespace acos::gui
