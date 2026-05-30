#pragma once
#include <acos/types.h>

namespace acos::ipc {

class Notification {
public:
    Notification();
    void signal();
    void wait();
    void reset();

    u64 id() const { return m_id; }
    u64 owner() const { return m_owner; }

private:
    u64 m_id;
    u64 m_owner;
    bool m_signaled;
};

} // namespace acos::ipc
