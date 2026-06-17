#include "hda.h"

namespace acos::drivers::audio {

IntelHDA::IntelHDA(u64 bar0) : m_bar0(bar0), m_regs(reinterpret_cast<volatile u8*>(bar0)) {}

bool IntelHDA::initialize() {
    if (!m_bar0) return false;

    // 1. Reset Controller
    volatile u32* gctl = reinterpret_cast<volatile u32*>(m_regs + 0x08);
    *gctl &= ~0x01; // Clear CRST
    while (*gctl & 0x01); // Wait for reset
    *gctl |= 0x01; // Set CRST
    while (!(*gctl & 0x01)); // Wait for ready

    // 2. Enable interrupts (future)

    // 3. Enumerate codecs (simplified)
    volatile u16* statests = reinterpret_cast<volatile u16*>(m_regs + 0x0E);
    u16 codecs = *statests;
    (void)codecs;

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
