#pragma once
#include <acos/types.h>
#include <acos/abi/input.h>
#include <kernel/hal/spinlock.h>
#include <kernel/scheduler/thread.h>

namespace acos::input {

using InputEvent = abi::InputEvent;

class InputQueue {
public:
    InputQueue();
    ~InputQueue();

    void push_event(const InputEvent& event);
    bool pop_event(InputEvent& event, bool block);

private:
    hal::SpinLock m_lock;
    static constexpr usize QUEUE_SIZE = 128;
    InputEvent m_events[QUEUE_SIZE];
    usize m_head;
    usize m_tail;
    usize m_count;

    scheduler::Thread* m_waiting_threads[16];
    usize m_wait_count;
};

} // namespace acos::input
