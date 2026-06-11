#pragma once
#include <acos/types.h>

namespace acos::display {

/// IPC message types for the display protocol.
/// Clients (DesktopShell, TerminalWindow, future apps) send these
/// to the DisplayServer over its command channel.
enum class DisplayMsgType : u32 {
    /// Create a new window. Sender becomes the owner.
    CreateWindow = 1,
    /// Destroy a window by ID. Only the owner may destroy.
    DestroyWindow = 2,
    /// Move a window to a new position.
    MoveWindow = 3,
    /// Resize a window.
    ResizeWindow = 4,
    /// Present (swap buffers) for a window's surface.
    /// The DS thread performs the swap and marks the region dirty.
    PresentSurface = 5,
    /// Notify the compositor that the desktop background changed.
    /// Triggers recomposition even without window damage.
    DamageNotify = 6,
    /// Write text to the terminal window's back buffer.
    /// Payload is a TerminalTextMsg.
    TerminalText = 7,
};

/// Maximum payload size carried inline in the IPC message.
static constexpr usize DISPLAY_MSG_MAX_PAYLOAD = 256;

/// Header common to all display protocol messages.
struct DisplayMsg {
    DisplayMsgType type;
    u32 _pad;
    union {
        struct {
            u32 x, y, width, height;
            u32 flags;
        } create_window;
        struct {
            u64 window_id;
        } destroy_window;
        struct {
            u64 window_id;
            u32 x, y;
        } move_window;
        struct {
            u64 window_id;
            u32 width, height;
        } resize_window;
        struct {
            u64 window_id;
        } present;
        struct {
            // No extra data — just triggers recomposition
        } damage;
        struct {
            u32 len;
            char data[DISPLAY_MSG_MAX_PAYLOAD - sizeof(u32)];
        } terminal_text;
    };
};

} // namespace acos::display
