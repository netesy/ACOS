#pragma once
#include <acos/types.h>
#include <kernel/graphics/framebuffer.h>
#include <kernel/graphics/renderer.h>

namespace acos::display {

class DisplayServer;
class Window;
struct Surface;

/// A terminal window rendered inside the display server.
/// Receives text from ConsoleNode::write and serial input,
/// draws it into a surface that the compositor blits to screen.
class TerminalWindow {
public:
    static constexpr u32 WIN_X      = 40;
    static constexpr u32 WIN_Y      = 60;
    static constexpr u32 WIN_WIDTH  = 640;
    static constexpr u32 WIN_HEIGHT = 440;

    TerminalWindow();

    /// Create the window + surface inside the given display server.
    /// Must be called after DisplayServer::initialize().
    bool initialize(DisplayServer* ds);

    /// Process a single character. Handles \n, \b, \r, printable.
    void put_char(char c);

    /// Process a string of characters.
    void put_string(const char* text, usize len);

    /// Redraw the surface and present to compositor.
    /// Called from the idle loop / run_tick.
    void redraw();

    bool is_initialized() const { return m_window != nullptr; }

private:
    static constexpr u32 FONT_W       = 8;
    static constexpr u32 FONT_H       = 16;
    static constexpr u32 TITLE_H      = 24;
    static constexpr u32 MAX_COLS     = 80;
    static constexpr u32 MAX_LINES    = 256;

    // Window / surface
    Window*  m_window;
    u64      m_surface_id;
    DisplayServer* m_ds;

    // Text buffer (circular line store)
    char m_lines[MAX_LINES][MAX_COLS + 1]; // +1 for '\0'
    u32  m_line_lengths[MAX_LINES];
    u32  m_total_lines;  // total lines ever written (scrolls)
    u32  m_visible_rows; // how many text rows fit in content area

    // Colors (ARGB)
    static constexpr u32 BG_COLOR      = 0xFF181818;
    static constexpr u32 FG_COLOR      = 0xFFCCCCCC;
    static constexpr u32 TITLE_BG      = 0xFF2D2D2D;
    static constexpr u32 TITLE_FG      = 0xFFCCCCCC;
    static constexpr u32 CURSOR_COLOR  = 0xFFCCCCCC;

    void scroll_up();
    void new_line();
};

// Global terminal instance (set by kernelMain)
extern TerminalWindow* g_terminal_window;

} // namespace acos::display
