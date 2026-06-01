#include "volume_indicator.h"
#include <userland/gui/theme.h>

namespace acos::shell {

VolumeIndicator::VolumeIndicator() : m_volume(50) {
    m_rect = {750, 5, 40, 30};
}

void VolumeIndicator::draw(acos::graphics::Renderer* renderer [[maybe_unused]]) {
    // For now, this is a placeholder
    // Full implementation would use the renderer to draw the volume indicator
}

} // namespace acos::shell
