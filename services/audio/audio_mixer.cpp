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
    if (!output_buffer || size == 0) return;
    
    i16* out = (i16*)output_buffer;
    usize samples = size / sizeof(i16);
    
    // Clear output buffer
    for (usize i = 0; i < samples; i++) {
        out[i] = 0;
    }
    
    // Mix all active streams
    for (usize i = 0; i < m_stream_count; i++) {
        AudioStream* stream = m_active_streams[i];
        if (!stream) continue;
        
        u32 volume = stream->volume();
        i32 vol_scale = (volume * 256) / 100;
        
        // Get samples from stream and mix
        for (usize j = 0; j < samples; j++) {
            i32 sample = 0; // Would get from stream buffer
            sample = (sample * vol_scale) / 256;
            sample = (sample * m_master_volume) / 100;
            
            i32 mixed = out[j] + sample;
            if (mixed > 32767) mixed = 32767;
            if (mixed < -32768) mixed = -32768;
            out[j] = (i16)mixed;
        }
    }
}

} // namespace acos::audio
