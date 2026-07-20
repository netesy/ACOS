#include <kernel/input/keyboard_manager.h>
#include <kernel/input/input_manager.h>

namespace acos::input {

using abi::VirtualKey;
using abi::InputType;
using abi::InputEvent;
namespace ModifierFlags = abi::ModifierFlags;

bool KeyboardManager::m_shift = false;
bool KeyboardManager::m_ctrl = false;
bool KeyboardManager::m_alt = false;

static VirtualKey ps2_to_vk[128] = {
    VirtualKey::None,      // 0
    VirtualKey::Escape,    // 1 (0x01)
    VirtualKey::Num1,      // 2
    VirtualKey::Num2,      // 3
    VirtualKey::Num3,      // 4
    VirtualKey::Num4,      // 5
    VirtualKey::Num5,      // 6
    VirtualKey::Num6,      // 7
    VirtualKey::Num7,      // 8
    VirtualKey::Num8,      // 9
    VirtualKey::Num9,      // 10
    VirtualKey::Num0,      // 11
    VirtualKey::Minus,     // 12
    VirtualKey::Equals,    // 13
    VirtualKey::Backspace, // 14
    VirtualKey::Tab,       // 15
    VirtualKey::Q,         // 16
    VirtualKey::W,         // 17
    VirtualKey::E,         // 18
    VirtualKey::R,         // 19
    VirtualKey::T,         // 20
    VirtualKey::Y,         // 21
    VirtualKey::U,         // 22
    VirtualKey::I,         // 23
    VirtualKey::O,         // 24
    VirtualKey::P,         // 25
    VirtualKey::LBracket,  // 26
    VirtualKey::RBracket,  // 27
    VirtualKey::Enter,     // 28
    VirtualKey::LCtrl,     // 29
    VirtualKey::A,         // 30
    VirtualKey::S,         // 31
    VirtualKey::D,         // 32
    VirtualKey::F,         // 33
    VirtualKey::G,         // 34
    VirtualKey::H,         // 35
    VirtualKey::J,         // 36
    VirtualKey::K,         // 37
    VirtualKey::L,         // 38
    VirtualKey::Semicolon, // 39
    VirtualKey::Quote,     // 40
    VirtualKey::Backtick,  // 41
    VirtualKey::LShift,    // 42
    VirtualKey::Backslash, // 43
    VirtualKey::Z,         // 44
    VirtualKey::X,         // 45
    VirtualKey::C,         // 46
    VirtualKey::V,         // 47
    VirtualKey::B,         // 48
    VirtualKey::N,         // 49
    VirtualKey::M,         // 50
    VirtualKey::Comma,     // 51
    VirtualKey::Period,    // 52
    VirtualKey::Slash,     // 53
    VirtualKey::RShift,    // 54
    VirtualKey::None,      // 55
    VirtualKey::LAlt,      // 56
    VirtualKey::Space,     // 57
    VirtualKey::CapsLock,  // 58
    VirtualKey::F1,        // 59
    VirtualKey::F2,        // 60
    VirtualKey::F3,        // 61
    VirtualKey::F4,        // 62
    VirtualKey::F5,        // 63
    VirtualKey::F6,        // 64
    VirtualKey::F7,        // 65
    VirtualKey::F8,        // 66
    VirtualKey::F9,        // 67
    VirtualKey::F10,       // 68
    VirtualKey::None,      // 69 (NumLock)
    VirtualKey::None,      // 70 (ScrollLock)
    VirtualKey::Home,      // 71
    VirtualKey::Up,        // 72
    VirtualKey::PageUp,    // 73
    VirtualKey::None,      // 74
    VirtualKey::Left,      // 75
    VirtualKey::None,      // 76
    VirtualKey::Right,     // 77
    VirtualKey::None,      // 78
    VirtualKey::End,       // 79
    VirtualKey::Down,      // 80
    VirtualKey::PageDown,  // 81
    VirtualKey::Insert,    // 82
    VirtualKey::Delete,    // 83
    VirtualKey::None,      // 84
    VirtualKey::None,      // 85
    VirtualKey::None,      // 86
    VirtualKey::F11,       // 87
    VirtualKey::F12,       // 88
};

void KeyboardManager::init() {
    m_shift = false;
    m_ctrl = false;
    m_alt = false;
}

void KeyboardManager::handle_scancode(u8 scancode) {
    bool released = (scancode & 0x80) != 0;
    u8 raw_scancode = scancode & 0x7F;

    // Update modifier states
    if (raw_scancode == 0x2A || raw_scancode == 0x36) {
        m_shift = !released;
    } else if (raw_scancode == 0x1D) {
        m_ctrl = !released;
    } else if (raw_scancode == 0x38) {
        m_alt = !released;
    }

    if (raw_scancode < 128) {
        VirtualKey vk = ps2_to_vk[raw_scancode];
        if (vk != VirtualKey::None) {
            InputEvent event;
            event.type = InputType::Keyboard;
            event.code = static_cast<u32>(vk);
            event.value = released ? 0 : 1; // 0 = released, 1 = pressed

            u32 flags = 0;
            if (m_shift) flags |= ModifierFlags::Shift;
            if (m_ctrl) flags |= ModifierFlags::Ctrl;
            if (m_alt) flags |= ModifierFlags::Alt;
            event.flags = flags;

            InputManager::push_event(event);
        }
    }
}

} // namespace acos::input
