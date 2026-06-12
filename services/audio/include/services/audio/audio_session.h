#pragma once
#include <acos/types.h>

namespace acos::audio {

class AudioSession {
public:
    AudioSession(u64 user_id);
    u64 user_id() const { return m_user_id; }

private:
    u64 m_user_id;
};

} // namespace acos::audio
