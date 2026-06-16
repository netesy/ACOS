#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/ipc.h>
#include <services/audio/audio_server.h>

namespace acos::audio {

AudioServer::AudioServer() : m_stream_count(0), m_next_stream_id(1), m_channel_handle(0), m_running(false) {}

bool AudioServer::initialize() {
    m_running = false;
    m_stream_count = 0;
    m_next_stream_id = 1;
    
    m_channel_handle = acos::ipc::channel_create();
    if (!m_channel_handle) return false;

    acos::services::register_service("audio_server", m_channel_handle);
    
    return true;
}

void AudioServer::run() {
    m_running = true;
    
    while (m_running) {
        // Process incoming IPC messages (non-blocking)
        acos::ipc::Message msg;
        if (acos::ipc::channel_receive(m_channel_handle, &msg, sizeof(msg))) {
            handle_request(msg);
        }
    }
}

void AudioServer::handle_request(const acos::ipc::Message& msg) {
    if (msg.size < sizeof(AudioRequest)) return;
    AudioRequest* req = (AudioRequest*)msg.payload;

    switch (req->type) {
        case AudioRequestType::CreateStream: {
            if (m_stream_count < 64) {
                AudioStream* stream = (AudioStream*)acos::memory::malloc(sizeof(AudioStream));
                if (stream) {
                    new (stream) AudioStream(m_next_stream_id++, msg.sender, req->create_stream.config);
                    m_streams[m_stream_count++] = stream;
                    m_mixer.add_stream(stream);
                }
            }
            break;
        }
        default:
            break;
    }
}

} // namespace acos::audio
