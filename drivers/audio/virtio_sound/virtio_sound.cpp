#include "virtio_sound.h"
#include <kernel/audio/audio_manager.h>

namespace acos::drivers::audio {

VirtIOSound::VirtIOSound() {}

bool VirtIOSound::initialize() {
    // In a real VirtIO driver, we would discover the device on the PCI bus
    // and setup the virtqueues.
    return true;
}

void VirtIOSound::shutdown() {}

bool VirtIOSound::create_stream(u32 device_id, const acos::audio::StreamConfig& config) {
    (void)device_id; (void)config;
    return true;
}

void VirtIOSound::destroy_stream(u32 device_id) { (void)device_id; }

bool VirtIOSound::submit_buffer(u32 device_id, const void* data, usize size) {
    (void)device_id; (void)data; (void)size;
    // Push buffer to VirtIO TX queue
    return true;
}

void VirtIOSound::pause(u32 device_id) { (void)device_id; }
void VirtIOSound::resume(u32 device_id) { (void)device_id; }
void VirtIOSound::stop(u32 device_id) { (void)device_id; }

} // namespace acos::drivers::audio
