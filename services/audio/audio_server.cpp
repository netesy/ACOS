#include "audio_server.h"
#include <kernel/audio/audio_manager.h>
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::audio {

AudioServer::AudioServer() : m_stream_count(0), m_next_stream_id(1), m_running(false) {}

bool AudioServer::initialize() {
    return true;
}

void AudioServer::run() {
    m_running = true;
    while (m_running) {
        acos::ipc::Message msg;
        if (m_channel.receive(msg, false)) {
            handle_request(msg);
        }
        // In a real system, the mixer would run on a high-priority thread or timer
    }
}

void AudioServer::handle_request(const acos::ipc::Message& msg) {
    if (msg.size < sizeof(AudioRequest)) return;
    AudioRequest* req = (AudioRequest*)msg.payload;

    switch (req->type) {
        case AudioRequestType::CreateStream: {
            if (m_stream_count < 64) {
                AudioStream* stream = (AudioStream*)acos::memory::kmalloc(sizeof(AudioStream));
                new (stream) AudioStream(m_next_stream_id++, msg.sender, req->create_stream.config);
                m_streams[m_stream_count++] = stream;
                m_mixer.add_stream(stream);
            }
            break;
        }
        default:
            break;
    }
}

} // namespace acos::audio
