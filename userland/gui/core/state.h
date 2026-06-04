#pragma once
#include "observable.h"
#include "../widget.h"

namespace acos::gui {

template <typename T>
class State : public Observable<T> {
public:
    State(Ref<Widget> owner, const T& initial_value)
        : Observable<T>(initial_value), m_owner(owner) {}

    void set(const T& value) override {
        if (!(this->m_value == value)) {
            this->m_value = value;
            this->notify();
            if (m_owner) {
                m_owner->set_layout_dirty();
            }
        }
    }

private:
    Ref<Widget> m_owner;
};

} // namespace acos::gui
