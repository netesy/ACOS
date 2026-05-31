#include "audio_stream.h"

namespace acos::audio {

AudioStream::AudioStream(u64 id, u64 owner_pid, const StreamConfig& config)
    : m_id(id), m_owner_pid(owner_pid), m_config(config), m_volume(100) {}

} // namespace acos::audio
