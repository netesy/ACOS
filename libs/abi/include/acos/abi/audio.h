#pragma once
#include <acos/types.h>

namespace acos::abi {

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

} // namespace acos::abi
