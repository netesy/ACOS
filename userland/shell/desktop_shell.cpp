#include "desktop_shell.h"

namespace acos::shell {

DesktopShell::DesktopShell() {}
void DesktopShell::initialize() {}
void DesktopShell::run() {}

void DesktopShell::draw([[maybe_unused]] acos::graphics::Renderer* renderer) {
    // In the new system, we'd use a UIContext and paint the render root.
}

} // namespace acos::shell
