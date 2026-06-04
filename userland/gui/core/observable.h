#pragma once
#include "vector.h"

namespace acos::gui {

template <typename T>
class Observable {
public:
    Observable(const T& initial_value) : m_value(initial_value) {}
    virtual ~Observable() {}

    const T& get() const { return m_value; }

    virtual void set(const T& value) {
        if (!(m_value == value)) {
            m_value = value;
            notify();
        }
    }

    void subscribe(void (*listener)(void*, const T&), void* context) {
        m_listeners.push_back({listener, context});
    }

protected:
    void notify() {
        for (auto& listener : m_listeners) {
            listener.func(listener.context, m_value);
        }
    }

    struct Listener {
        void (*func)(void*, const T&);
        void* context;
    };

    T m_value;
    Vector<Listener> m_listeners;
};

} // namespace acos::gui
