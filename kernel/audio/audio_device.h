#pragma once
#include <acos/types.h>
#include "audio_driver.h"

namespace acos::audio {

struct DeviceCapabilities {
    bool playback;
    bool recording;
    bool duplex;
    u32 max_sample_rate;
    u32 max_channels;
};

class AudioDevice {
public:
    AudioDevice(u32 id, const char* name, AudioDriver* driver);

    u32 id() const { return m_id; }
    const char* name() const { return m_name; }
    AudioDriver* driver() const { return m_driver; }

    const DeviceCapabilities& caps() const { return m_caps; }
    void set_caps(const DeviceCapabilities& caps) { m_caps = caps; }

private:
    u32 m_id;
    const char* m_name;
    AudioDriver* m_driver;
    DeviceCapabilities m_caps;
};

} // namespace acos::audio
