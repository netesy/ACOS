#pragma once
#include <acos/types.h>

namespace acos::gui::widgets {

template <typename... Args>
class Signal {
public:
    using Slot = void (*)(void*, Args...);

    struct Connection {
        void* receiver;
        Slot slot;
    };

    Signal() : m_count(0) {}

    void connect(void* receiver, Slot slot) {
        if (m_count < 8) {
            m_slots[m_count++] = {receiver, slot};
        }
    }

    void emit(Args... args) {
        for (u32 i = 0; i < m_count; i++) {
            m_slots[i].slot(m_slots[i].receiver, args...);
        }
    }

private:
    Connection m_slots[8];
    u32 m_count;
};

} // namespace acos::gui::widgets
