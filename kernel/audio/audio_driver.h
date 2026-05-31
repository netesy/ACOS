#pragma once
#include <acos/types.h>

namespace acos::audio {

enum class AudioFormat : u32 {
    PCM16,
    PCM32,
    FLOAT32
};

struct StreamConfig {
    AudioFormat format;
    u32 sample_rate;
    u32 channels;
    u32 buffer_size;
};

class AudioDriver {
public:
    virtual ~AudioDriver() = default;

    virtual bool initialize() = 0;
    virtual void shutdown() = 0;

    virtual bool create_stream(u32 device_id, const StreamConfig& config) = 0;
    virtual void destroy_stream(u32 device_id) = 0;

    virtual bool submit_buffer(u32 device_id, const void* data, usize size) = 0;
    virtual void pause(u32 device_id) = 0;
    virtual void resume(u32 device_id) = 0;
    virtual void stop(u32 device_id) = 0;
};

} // namespace acos::audio
