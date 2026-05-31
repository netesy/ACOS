#pragma once
#include "audio_protocol.h"
#include "audio_mixer.h"
#include <kernel/ipc/channel.h>

namespace acos::audio {

class AudioServer {
public:
    AudioServer();
    bool initialize();
    void run();

private:
    void handle_request(const acos::ipc::Message& msg);

    AudioMixer m_mixer;
    AudioStream* m_streams[64];
    usize m_stream_count;
    u64 m_next_stream_id;

    acos::ipc::Channel m_channel;
    bool m_running;
};

} // namespace acos::audio
