#include "audio_settings.h"
#include <userland/gui/theme.h>

namespace acos::apps {

AudioSettings::AudioSettings() : m_title("Audio Settings") {
    m_rect = {0, 0, 400, 300};
}

void AudioSettings::draw(acos::graphics::Renderer* renderer) {
    m_title.draw(renderer);
    m_device_list.draw(renderer);
}

} // namespace acos::apps
