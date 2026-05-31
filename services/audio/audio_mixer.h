#pragma once
#include "audio_stream.h"

namespace acos::audio {

class AudioMixer {
public:
    AudioMixer();
    void mix(void* output_buffer, usize size);
    void add_stream(AudioStream* stream);
    void remove_stream(u64 stream_id);

    void set_master_volume(u32 vol) { m_master_volume = vol; }

private:
    AudioStream* m_active_streams[32];
    usize m_stream_count;
    u32 m_master_volume;
};

} // namespace acos::audio
