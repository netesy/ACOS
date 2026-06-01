#include "audio_server.h"
#include <kernel/audio/audio_manager.h>
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::audio {

AudioServer::AudioServer() : m_stream_count(0), m_next_stream_id(1), m_running(false) {}

bool AudioServer::initialize() {
    m_running = false;
    m_stream_count = 0;
    m_next_stream_id = 1;
    
    // Initialize audio manager
    acos::audio::AudioManager::init();
    
    // Register with service manager when the service registry is active
    // Service registry call is documented here until service startup order is finalized
    // acos::services::ServiceManager::register_service(
    //     acos::services::ServiceId::Audio, 
    //     acos::scheduler::current_thread()->parent->id
    // );
    
    return true;
}

void AudioServer::run() {
    m_running = true;
    
    // Audio server main loop:
    // 1. Process incoming IPC requests (create/destroy streams, etc.)
    // 2. Run mixer to blend audio streams
    // 3. Submit mixed audio to hardware
    // 4. Handle timing and synchronization
    
    while (m_running) {
        // Process incoming IPC messages (non-blocking)
        acos::ipc::Message msg;
        if (m_channel.receive(msg, false)) {
            handle_request(msg);
        }
        
        // Mixer scheduling policy:
        // This server processes control requests; audio devices drive mixing cadence.
        // The mixer should be driven by:
        // - Hardware timer interrupts (e.g., every 10ms)
        // - Or a dedicated high-priority mixer thread
        // - Or a combination of both
        
        // Mix audio streams once an output device buffer is available
        // m_mixer.mix(output_buffer, buffer_size);
        
        // Submit mixed audio to hardware
        // This would typically involve:
        // - Getting the mixed buffer from the mixer
        // - Submitting it to the audio device via DMA
        // - Waiting for completion
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
