#pragma once
#include <kernel/audio/audio_driver.h>

namespace acos::drivers::audio {

class IntelHDA : public acos::audio::AudioDriver {
public:
    IntelHDA(u64 bar0);
    bool initialize() override;
    void shutdown() override;

    bool create_stream(u32 device_id, const acos::audio::StreamConfig& config) override;
    void destroy_stream(u32 device_id) override;

    bool submit_buffer(u32 device_id, const void* data, usize size) override;
    void pause(u32 device_id) override;
    void resume(u32 device_id) override;
    void stop(u32 device_id) override;

private:
    u64 m_bar0;
    volatile u8* m_regs;
};

} // namespace acos::drivers::audio
