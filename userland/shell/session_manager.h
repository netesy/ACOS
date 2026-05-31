#pragma once
#include <acos/types.h>

namespace acos::shell {

class SessionManager {
public:
    SessionManager();
    void start_session(u64 user_id);
    void end_session();

private:
    u64 m_current_user;
    bool m_active;
};

} // namespace acos::shell
