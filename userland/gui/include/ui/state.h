#pragma once
#include <ui/ref.h>

namespace acos::ui {

template<typename T>
class State {
public:
    State(T value) : m_value(value) {}

    T get() const { return m_value; }
    void set(T value) {
        m_value = value;
        // Trigger rebuild of subscribers
    }

private:
    T m_value;
};

} // namespace acos::ui
