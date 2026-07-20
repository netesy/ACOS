#include <kernel/input/input_manager.h>
#include <kernel/input/keyboard.h>
#include <kernel/input/mouse.h>
#include <kernel/input/keyboard_manager.h>
#include <kernel/input/mouse_manager.h>
#include <kernel/hal/serial.h>

namespace acos::input {

class PS2Keyboard : public KeyboardDevice {
public:
    bool initialize() override { return true; }
    const char* name() const override { return "PS/2 Keyboard"; }
    void handle_scancode(u8 scancode) override {
        KeyboardManager::handle_scancode(scancode);
    }
};

class PS2Mouse : public MouseDevice {
public:
    bool initialize() override { return true; }
    const char* name() const override { return "PS/2 Mouse"; }
    void handle_movement(i32 dx, i32 dy) override {
        MouseManager::handle_movement(dx, dy);
    }
    void handle_button(u32 button, bool pressed) override {
        MouseManager::handle_button(button, pressed);
    }
};

static PS2Keyboard g_ps2_keyboard;
static PS2Mouse g_ps2_mouse;

hal::SpinLock InputManager::m_lock;
InputDevice* InputManager::m_devices[16];
usize InputManager::m_device_count = 0;
InputManager::QueueEntry InputManager::m_queues[16];
usize InputManager::m_queue_count = 0;
u64 InputManager::m_focused_pid = 0;

InputEvent InputManager::m_legacy_queue[64];
usize InputManager::m_legacy_head = 0;
usize InputManager::m_legacy_tail = 0;
usize InputManager::m_legacy_count = 0;

static void run_input_self_test() {
    hal::serial_print("[Input Self-Test] Starting...\n");

    // 1. Create a queue
    InputQueue queue;
    InputManager::register_queue(&queue, 99);

    // 2. Set focus
    InputManager::set_focused_process(99);

    // 3. Push a keyboard event
    InputEvent kbd_event;
    kbd_event.type = abi::InputType::Keyboard;
    kbd_event.code = static_cast<u32>(abi::VirtualKey::A);
    kbd_event.value = 1; // Pressed
    kbd_event.flags = abi::ModifierFlags::Shift;
    InputManager::push_event(kbd_event);

    // 4. Push a mouse event
    InputEvent mouse_event;
    mouse_event.type = abi::InputType::Mouse;
    mouse_event.code = (120 << 16) | 340; // (120, 340)
    mouse_event.value = 1; // Left button pressed
    mouse_event.flags = 0;
    InputManager::push_event(mouse_event);

    // 5. Pop and verify keyboard event
    InputEvent popped;
    bool ok = queue.pop_event(popped, false);
    if (!ok || popped.type != abi::InputType::Keyboard || popped.code != static_cast<u32>(abi::VirtualKey::A) || popped.value != 1 || popped.flags != abi::ModifierFlags::Shift) {
        hal::serial_print("[Input Self-Test] FAILED to pop keyboard event!\n");
        return;
    }
    hal::serial_print("[Input Self-Test] Keyboard event popped and verified.\n");

    // 6. Pop and verify mouse event
    ok = queue.pop_event(popped, false);
    if (!ok || popped.type != abi::InputType::Mouse || popped.code != ((120 << 16) | 340) || popped.value != 1) {
        hal::serial_print("[Input Self-Test] FAILED to pop mouse event!\n");
        return;
    }
    hal::serial_print("[Input Self-Test] Mouse event popped and verified.\n");

    // 7. Verify no more events
    ok = queue.pop_event(popped, false);
    if (ok) {
        hal::serial_print("[Input Self-Test] FAILED: popped extra event!\n");
        return;
    }

    // 8. Unregister
    InputManager::unregister_queue(&queue);
    InputManager::set_focused_process(0);

    hal::serial_print("[Input Self-Test] PASSED successfully!\n");
}

void InputManager::init() {
    register_device(&g_ps2_keyboard);
    register_device(&g_ps2_mouse);

    KeyboardManager::init();
    MouseManager::init();

    // Run freestanding self-test suite
    run_input_self_test();
}

void InputManager::register_device(InputDevice* dev) {
    hal::ScopedLock lock(m_lock);
    if (m_device_count < 16) {
        m_devices[m_device_count++] = dev;
    }
}

void InputManager::register_queue(InputQueue* queue, u64 pid) {
    hal::ScopedLock lock(m_lock);
    if (m_queue_count < 16) {
        m_queues[m_queue_count++] = {queue, pid};
    }
}

void InputManager::unregister_queue(InputQueue* queue) {
    hal::ScopedLock lock(m_lock);
    for (usize i = 0; i < m_queue_count; i++) {
        if (m_queues[i].queue == queue) {
            for (usize j = i; j < m_queue_count - 1; j++) {
                m_queues[j] = m_queues[j + 1];
            }
            m_queue_count--;
            break;
        }
    }
}

void InputManager::push_event(const InputEvent& event) {
    hal::ScopedLock lock(m_lock);

    // Push to legacy queue for backwards compatibility
    if (m_legacy_count < 64) {
        m_legacy_queue[m_legacy_tail] = event;
        m_legacy_tail = (m_legacy_tail + 1) % 64;
        m_legacy_count++;
    }

    // Route to queues belonging to the focused process,
    // or to ALL queues if no process has focus.
    bool routed = false;
    if (m_focused_pid != 0) {
        for (usize i = 0; i < m_queue_count; i++) {
            if (m_queues[i].pid == m_focused_pid) {
                m_queues[i].queue->push_event(event);
                routed = true;
            }
        }
    }

    if (!routed) {
        for (usize i = 0; i < m_queue_count; i++) {
            m_queues[i].queue->push_event(event);
        }
    }
}

bool InputManager::pop_event(InputEvent& event) {
    hal::ScopedLock lock(m_lock);
    if (m_legacy_count == 0) return false;
    event = m_legacy_queue[m_legacy_head];
    m_legacy_head = (m_legacy_head + 1) % 64;
    m_legacy_count--;
    return true;
}

void InputManager::set_focused_process(u64 pid) {
    hal::ScopedLock lock(m_lock);
    m_focused_pid = pid;
}

InputDevice* InputManager::get_device_by_type(InputType type) {
    hal::ScopedLock lock(m_lock);
    for (usize i = 0; i < m_device_count; i++) {
        if (m_devices[i] && m_devices[i]->type() == type) {
            return m_devices[i];
        }
    }
    return nullptr;
}

} // namespace acos::input
