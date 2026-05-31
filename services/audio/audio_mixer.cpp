#include "audio_mixer.h"

namespace acos::audio {

AudioMixer::AudioMixer() : m_stream_count(0), m_master_volume(100) {}

void AudioMixer::add_stream(AudioStream* stream) {
    if (m_stream_count < 32) {
        m_active_streams[m_stream_count++] = stream;
    }
}

void AudioMixer::remove_stream(u64 stream_id) {
    for (usize i = 0; i < m_stream_count; i++) {
        if (m_active_streams[i]->id() == stream_id) {
            m_active_streams[i] = m_active_streams[--m_stream_count];
            break;
        }
    }
}

void AudioMixer::mix(void* output_buffer, usize size) {
    (void)output_buffer; (void)size;
    // Basic additive mixing logic would go here
}

} // namespace acos::audio
