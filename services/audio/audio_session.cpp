#include <acos/process.h>
#include <acos/runtime.h>
#include <services/audio/audio_session.h>

namespace acos::audio {

AudioSession::AudioSession(u64 user_id) : m_user_id(user_id) {}

} // namespace acos::audio
