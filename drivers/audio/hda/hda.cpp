#include "hda.h"

namespace acos::drivers::audio {

IntelHDA::IntelHDA() {}

bool IntelHDA::initialize() {
    // Discovery of PCI controller and HDA codecs
    return true;
}

void IntelHDA::shutdown() {}

bool IntelHDA::create_stream(u32 device_id, const acos::audio::StreamConfig& config) {
    (void)device_id; (void)config;
    return true;
}

void IntelHDA::destroy_stream(u32 device_id) { (void)device_id; }

bool IntelHDA::submit_buffer(u32 device_id, const void* data, usize size) {
    (void)device_id; (void)data; (void)size;
    return true;
}

void IntelHDA::pause(u32 device_id) { (void)device_id; }
void IntelHDA::resume(u32 device_id) { (void)device_id; }
void IntelHDA::stop(u32 device_id) { (void)device_id; }

} // namespace acos::drivers::audio
