#include "audio_manager.h"

namespace acos::audio {

AudioDevice* AudioManager::g_devices[16];
u32 AudioManager::g_device_count = 0;

void AudioManager::init() {
    g_device_count = 0;
}

void AudioManager::register_device(AudioDevice* device) {
    if (g_device_count < 16) {
        g_devices[g_device_count++] = device;
    }
}

AudioDevice* AudioManager::get_device(u32 id) {
    for (u32 i = 0; i < g_device_count; i++) {
        if (g_devices[i]->id() == id) return g_devices[i];
    }
    return nullptr;
}

u32 AudioManager::device_count() {
    return g_device_count;
}

} // namespace acos::audio
