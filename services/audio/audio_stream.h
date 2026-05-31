#pragma once
#include <acos/types.h>
#include <kernel/audio/audio_driver.h>

namespace acos::audio {

class AudioStream {
public:
    AudioStream(u64 id, u64 owner_pid, const StreamConfig& config);

    u64 id() const { return m_id; }
    u64 owner_pid() const { return m_owner_pid; }
    const StreamConfig& config() const { return m_config; }

    void set_volume(u32 vol) { m_volume = vol; }
    u32 volume() const { return m_volume; }

private:
    u64 m_id;
    u64 m_owner_pid;
    StreamConfig m_config;
    u32 m_volume;
};

} // namespace acos::audio
