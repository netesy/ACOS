#pragma once
#include <acos/types.h>
#include <acos/abi/audio.h>

namespace acos::audio {
using namespace ::acos::abi;

enum class AudioRequestType : u32 {
    GetDevices = 1,
    SelectDevice = 2,
    CreateStream = 3,
    DestroyStream = 4,
    StartStream = 5,
    StopStream = 6,
    SubmitBuffer = 7,
    SetVolume = 8
};

struct AudioRequest {
    AudioRequestType type;
    union {
        struct {
            u32 device_id;
        } select_device;
        struct {
            u32 device_id;
            StreamConfig config;
        } create_stream;
        struct {
            u64 stream_id;
        } stream_op;
        struct {
            u64 stream_id;
            u32 volume; // 0-100
        } set_volume;
    };
};

} // namespace acos::audio
