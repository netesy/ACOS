#pragma once
#include "audio_device.h"

namespace acos::audio {

class AudioManager {
public:
    static void register_device(AudioDevice* device);
    static AudioDevice* get_device(u32 id);
    static u32 device_count();
    static void init();

private:
    static AudioDevice* g_devices[16];
    static u32 g_device_count;
};

} // namespace acos::audio
