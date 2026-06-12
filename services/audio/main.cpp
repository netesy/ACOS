#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/process.h>
#include <services/audio/audio_server.h>

using namespace acos;
using namespace acos::audio;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    u64 audio_channel = ipc::channel_create();
    if (!audio_channel) return 1;

    if (!services::register_service("audio_server", audio_channel)) return 2;

    AudioServer server;
    if (!server.initialize()) return 3;

    server.run();
    return 0;
}
