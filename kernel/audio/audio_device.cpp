#include "audio_device.h"

namespace acos::audio {

AudioDevice::AudioDevice(u32 id, const char* name, AudioDriver* driver)
    : m_id(id), m_name(name), m_driver(driver) {
    m_caps = {true, false, false, 48000, 2};
}

} // namespace acos::audio
