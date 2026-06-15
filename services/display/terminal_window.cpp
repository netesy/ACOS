#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/graphics.h>
#include <acos/font_manager.h>
#include <services/display/terminal_window.h>
#include <services/display/display_server.h>
#include <services/display/display_protocol.h>
#include <services/display/window.h>
#include <services/display/surface_manager.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::display {

TerminalWindow* g_terminal_window = nullptr;

TerminalWindow::TerminalWindow()
    : m_window(nullptr), m_surface_id(0), m_ds(nullptr),
      m_total_lines(0), m_visible_rows(0) {
    for (u32 i = 0; i < MAX_LINES; i++) {
        m_lines[i][0] = '\0';
        m_line_lengths[i] = 0;
    }
}

bool TerminalWindow::initialize(DisplayServer* ds) {
    if (!ds) return false;
    m_ds = ds;

    // Create a window directly (bypass IPC)
    // We need to push a window into the display server's window array.
    // The simplest path: construct a GraphicsRequest via the channel.
    // But since we're in the kernel, we can call handle_request directly
    // by synthesising a message. Instead, let's use a helper on the
    // display server.
    //
    // For now, we create the window by pushing directly into the
    // display server's arrays.  The display server owns the memory.

    // We can't directly access private members, so use a public helper.
    // Add create_terminal_window() to DisplayServer.
    // For the initial version, we'll allocate everything here and
    // let the display server know about us via a setter.

    // Allocate the Window object
    void* win_mem = acos::memory::malloc(sizeof(Window));
    if (!win_mem) return false;

    // Window ID = 1 (first user window)
    m_window = new (win_mem) Window(1, 0, WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT);

    // Create a surface for the window content
    Surface* surface = ds->surface_manager_ref().create_surface(0, WIN_WIDTH, WIN_HEIGHT);
    if (!surface) {
        acos::memory::free(win_mem);
        m_window = nullptr;
        return false;
    }
    m_window->set_surface_id(surface->id);
    m_surface_id = surface->id;

    // Register window with the display server
    ds->add_window(m_window);

    // Calculate visible rows
    u32 content_h = WIN_HEIGHT - TITLE_H;
    m_visible_rows = content_h / FONT_H;
    if (m_visible_rows > MAX_LINES) m_visible_rows = MAX_LINES;

    // Clear the surface to background color
    u32* buf = surface->back_buffer ? surface->back_buffer : surface->buffer;
    for (u32 i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++) {
        buf[i] = BG_COLOR;
    }

    // Initial message
    put_string("ACOS Terminal v1.0\n", 20);
    put_string("Type 'help' for commands.\n\n", 28);

    // Draw initial frame
    redraw();

    return true;
}

void TerminalWindow::put_char(char c) {
    if (c == '\n' || c == '\r') {
        new_line();
    } else if (c == '\b') {
        // Backspace: delete last character on current line
        if (m_total_lines == 0) return;
        u32 idx = (m_total_lines - 1) % MAX_LINES;
        if (m_line_lengths[idx] > 0) {
            m_line_lengths[idx]--;
            m_lines[idx][m_line_lengths[idx]] = '\0';
        }
    } else if (c >= 32 && c < 127) {
        // Printable ASCII
        if (m_total_lines == 0) {
            // First line
            m_total_lines = 1;
            m_lines[0][0] = '\0';
            m_line_lengths[0] = 0;
        }
        u32 idx = (m_total_lines - 1) % MAX_LINES;
        if (m_line_lengths[idx] < MAX_COLS) {
            m_lines[idx][m_line_lengths[idx]] = c;
            m_line_lengths[idx]++;
            m_lines[idx][m_line_lengths[idx]] = '\0';
        }
    }
}

void TerminalWindow::put_string(const char* text, usize len) {
    for (usize i = 0; i < len; i++) {
        put_char(text[i]);
    }
}

void TerminalWindow::new_line() {
    // Start a new empty line
    if (m_total_lines >= MAX_LINES) {
        scroll_up();
    }
    u32 idx = m_total_lines % MAX_LINES;
    m_lines[idx][0] = '\0';
    m_line_lengths[idx] = 0;
    m_total_lines++;
}

void TerminalWindow::scroll_up() {
    // Scroll: shift all visible lines up by one
    for (u32 i = 0; i < MAX_LINES - 1; i++) {
        for (u32 j = 0; j <= MAX_COLS; j++) {
            m_lines[i][j] = m_lines[i + 1][j];
        }
        m_line_lengths[i] = m_line_lengths[i + 1];
    }
    m_lines[MAX_LINES - 1][0] = '\0';
    m_line_lengths[MAX_LINES - 1] = 0;
    if (m_total_lines > 0) m_total_lines--;
}

void TerminalWindow::redraw() {
    if (!m_window || !m_ds) return;

    Surface* surface = m_ds->surface_manager_ref().get_surface(m_surface_id);
    if (!surface) return;

    // Draw into the back buffer
    u32* buf = surface->back_buffer ? surface->back_buffer : surface->buffer;

    // Create a Framebuffer wrapping the back buffer
    acos::graphics::Framebuffer fb(reinterpret_cast<u64>(buf),
                   WIN_WIDTH * WIN_HEIGHT * sizeof(u32),
                   WIN_WIDTH, WIN_HEIGHT,
                   WIN_WIDTH,  // pitch = width for tightly packed
                   32);

    // Clear background
    fb.fill_rect(0, 0, WIN_WIDTH, WIN_HEIGHT, BG_COLOR);

    // Title bar
    fb.fill_rect(0, 0, WIN_WIDTH, TITLE_H, TITLE_BG);

    // Title text - draw using the console font directly
    acos::graphics::Font* font = acos::graphics::FontManager::get_console_font();
    if (font && font->is_valid()) {
        const char* title = " ACOS Terminal";
        u32 tx = 4;
        for (usize i = 0; title[i]; i++) {
            const u8* glyph = font->get_glyph(title[i]);
            if (glyph) {
                for (u32 gy = 0; gy < font->height(); gy++) {
                    for (u32 gx = 0; gx < font->width(); gx++) {
                        if (glyph[gy] & (0x80 >> gx)) {
                            u32 px = tx + gx;
                            u32 py = 4 + gy;
                            if (px < WIN_WIDTH && py < TITLE_H) {
                                buf[py * WIN_WIDTH + px] = TITLE_FG;
                            }
                        }
                    }
                }
            }
            tx += font->width();
        }

        // Draw text content
        u32 start_line = 0;
        if (m_total_lines > m_visible_rows) {
            start_line = m_total_lines - m_visible_rows;
        }

        for (u32 row = 0; row < m_visible_rows && (start_line + row) < m_total_lines; row++) {
            u32 line_idx = (start_line + row) % MAX_LINES;
            u32 y = TITLE_H + row * FONT_H;

            for (u32 col = 0; col < m_line_lengths[line_idx]; col++) {
                char ch = m_lines[line_idx][col];
                if (ch < 32 || ch >= 127) continue;

                const u8* glyph = font->get_glyph(ch);
                if (!glyph) continue;

                u32 x = col * FONT_W;
                for (u32 gy = 0; gy < FONT_H; gy++) {
                    for (u32 gx = 0; gx < FONT_W; gx++) {
                        if (glyph[gy] & (0x80 >> gx)) {
                            u32 px = x + gx;
                            u32 py = y + gy;
                            if (px < WIN_WIDTH && py < WIN_HEIGHT) {
                                buf[py * WIN_WIDTH + px] = FG_COLOR;
                            }
                        }
                    }
                }
            }
        }

        // Draw cursor on the last line
        if (m_total_lines > 0) {
            u32 last_idx = (m_total_lines - 1) % MAX_LINES;
            u32 cursor_row = m_total_lines - 1;
            if (cursor_row >= start_line) {
                u32 row_in_view = cursor_row - start_line;
                u32 cx = m_line_lengths[last_idx] * FONT_W;
                u32 cy = TITLE_H + row_in_view * FONT_H;
                // Blink-style: draw solid cursor
                for (u32 gy = 0; gy < FONT_H; gy++) {
                    for (u32 gx = 0; gx < FONT_W; gx++) {
                        u32 px = cx + gx;
                        u32 py = cy + gy;
                        if (px < WIN_WIDTH && py < WIN_HEIGHT) {
                            // XOR for visibility
                            buf[py * WIN_WIDTH + px] = (buf[py * WIN_WIDTH + px] == BG_COLOR)
                                ? CURSOR_COLOR : BG_COLOR;
                        }
                    }
                }
            }
        }
    }

    // Present via IPC: send PresentSurface to DS thread.
    // The DS thread performs the buffer swap and marks the region dirty.
    // This decouples the rendering thread from the compositing thread.
    DisplayMsg cmd{};
    cmd.type = DisplayMsgType::PresentSurface;
    cmd.present.window_id = m_window->id();
    m_ds->send_command(cmd);
}

} // namespace acos::display
