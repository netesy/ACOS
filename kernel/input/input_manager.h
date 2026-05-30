#pragma once
#include <kernel/input/input_device.h>

namespace acos::input {

class InputManager {
public:
    static void register_device(InputDevice* dev);
    static void push_event(const InputEvent& event);
    static bool pop_event(InputEvent& event);
    static void init();

private:
    static InputDevice* g_devices[8];
    static u32 g_device_count;

    static InputEvent g_event_queue[64];
    static usize g_head;
    static usize g_tail;
    static usize g_count;
};

} // namespace acos::input
