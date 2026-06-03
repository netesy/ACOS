#include <ui/event.h>
#include <ui/widget.h>
#include <ui/context.h>

namespace acos::ui {

void EventDispatcher::dispatch([[maybe_unused]] UIContext* ctx, Ref<Widget> root, [[maybe_unused]] UIEvent& event) {
    if (root.is_null()) return;
}

void EventDispatcher::capture_phase([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Ref<Widget> target, [[maybe_unused]] UIEvent& event) {}
void EventDispatcher::bubble_phase([[maybe_unused]] UIContext* ctx, [[maybe_unused]] Ref<Widget> target, [[maybe_unused]] UIEvent& event) {}

} // namespace acos::ui
