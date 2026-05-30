#include <kernel/input/input_manager.h>

namespace acos::input {

InputDevice* InputManager::g_devices[8];
u32 InputManager::g_device_count = 0;
InputEvent InputManager::g_event_queue[64];
usize InputManager::g_head = 0;
usize InputManager::g_tail = 0;
usize InputManager::g_count = 0;

void InputManager::register_device(InputDevice* dev) {
    if (g_device_count < 8) {
        g_devices[g_device_count++] = dev;
    }
}

void InputManager::push_event(const InputEvent& event) {
    if (g_count < 64) {
        g_event_queue[g_tail] = event;
        g_tail = (g_tail + 1) % 64;
        g_count++;
    }
}

bool InputManager::pop_event(InputEvent& event) {
    if (g_count == 0) return false;
    event = g_event_queue[g_head];
    g_head = (g_head + 1) % 64;
    g_count--;
    return true;
}

void InputManager::init() {}

} // namespace acos::input
