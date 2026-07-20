#pragma once
#include <kernel/input/input_device.h>
#include <kernel/input/input_queue.h>
#include <kernel/hal/spinlock.h>

namespace acos::input {

class InputManager {
public:
    static void init();

    static void register_device(InputDevice* dev);
    static void register_queue(InputQueue* queue, u64 pid);
    static void unregister_queue(InputQueue* queue);

    static void push_event(const InputEvent& event);
    static bool pop_event(InputEvent& event); // Legacy/fallback compatibility

    static void set_focused_process(u64 pid);
    static u64 focused_process() { return m_focused_pid; }

    static InputDevice* get_device_by_type(InputType type);

private:
    static hal::SpinLock m_lock;

    static InputDevice* m_devices[16];
    static usize m_device_count;

    struct QueueEntry {
        InputQueue* queue;
        u64 pid;
    };
    static QueueEntry m_queues[16];
    static usize m_queue_count;

    static u64 m_focused_pid;

    // Legacy queue for fallback compatibility
    static InputEvent m_legacy_queue[64];
    static usize m_legacy_head;
    static usize m_legacy_tail;
    static usize m_legacy_count;
};

} // namespace acos::input
