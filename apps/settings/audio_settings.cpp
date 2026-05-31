#include "audio_settings.h"
#include <userland/gui/theme.h>

namespace acos::apps {

AudioSettings::AudioSettings() : m_title("Audio Settings") {
    m_rect = {0, 0, 400, 300};
}

void AudioSettings::draw(u32* buffer, u32 pitch) {
    m_title.draw(buffer, pitch);
    m_device_list.draw(buffer, pitch);
}

} // namespace acos::apps
