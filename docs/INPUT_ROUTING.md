# Unified Input Event System & Routing Architecture

This document specifies the architecture, boundaries, and routing of the Unified Input Event System in Asade.

---

## Architecture Flow Diagram

```
              PS/2 Keyboard
                    │  (IRQ 1)
              PS/2 Mouse
                    │  (IRQ 12)
                    ▼
             Input Manager      (ACOS Core Kernel)
                    │
              Input Event Queue  (Per-Process Kernel Queue)
                    │  (Syscall: InputQueuePop)
                    ▼
             Window Manager      (Display Server / desktop.elf)
              │           │
         Keyboard       Mouse
           Focus        Hit Test
              │           │
              └─────┬─────┘
                    ▼
                Active App       (Active App Widget / Window)
                    │
                    ▼
                   IPC
```

---

## 1. Input Event Generation & Kernel Ingestion

When physical hardware interrupts are triggered by the keyboard (IRQ 1) or mouse (IRQ 12):
1. **Interrupt Service Routines (ISRs)**:
   - `isr_kbd_handler` routes to `PS2Controller::handle_keyboard_interrupt()`
   - `isr_mouse_handler` routes to `PS2Controller::handle_mouse_interrupt()`
2. **PS/2 Ingestion & Parsing**:
   - The PS/2 driver performs packet accumulation and parses scancodes into virtual keys, and mouse movements/button actions into unified events.
   - Synchronization checks ensure mouse packet streams are aligned (discarding misaligned packets).
3. **Kernel Input Ingestion**:
   - Keyboard/Mouse managers convert parsed state into `acos::abi::InputEvent` structures.
   - `InputManager::push_event(event)` is called.

---

## 2. Input Delivery Boundary: Per-Process Kernel Input Queues

Rather than using complex IPC pipelines for early-stage delivery, Asade establishes **per-process kernel input queues** as the input delivery boundary.

- **Queue Creation**: Any process can request its own input queue handle via `syscall(sys::SyscallNum::InputQueueCreate)`. The kernel allocates an `InputQueue` resource and registers it with the `InputManager` mapped to the process's PID.
- **Event Pulling**: Applications poll or block-retrieve events from their queue using `syscall(sys::SyscallNum::InputQueuePop, queue_handle, &event, block)`.
- **Focused Input Routing**:
  - To prevent input spying and save CPU cycles, the kernel's `InputManager` implements **Active Process Input Routing**.
  - If a specific process is focused (i.e. `m_focused_pid != 0`), `InputManager::push_event` routes input events **only** to the queue belonging to that focused process.
  - The focused process PID is set dynamically via the `sys::SyscallNum::InputFocusSet` syscall.

---

## 3. Userspace Window Manager (Display Server) Routing

Inside userspace, the **Display Server** (or **Desktop Shell**) acts as the supreme Window Manager:

1. **Active Event Loop**:
   - Polles events from its registered `m_input_queue` via `acos::input::pop_event`.
2. **Mouse Hit-Testing**:
   - When a Mouse event is popped, the Display Server's `InputRouter` extracts the coordinates `(x, y)`.
   - It performs z-ordered hit-testing across active windows to find the topmost target window.
3. **Window Focus Management**:
   - If the topmost target window is clicked, the `InputRouter` sets it as the active window.
   - It updates the kernel's active input routing process by calling `acos::input::set_focused_process(window->owner_pid())`.
4. **Keyboard Focus & Routing**:
   - Keyboard events are directly delivered to the window currently holding keyboard focus.
5. **App Ingestion**:
   - The event is dispatched to the target application window, which processes it locally or propagates it through GUI widgets using the event bubble phase.
