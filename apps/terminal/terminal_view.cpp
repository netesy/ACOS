#include "terminal_view.h"
#include <userland/gui/core/context.h>
#include <userland/gui/core/render_widgets.h>
#include <acos/font_manager.h>
#include <acos/renderer.h>

namespace acos::apps {

using abi::VirtualKey;
using abi::InputType;
namespace ModifierFlags = abi::ModifierFlags;

class RenderTerminal : public gui::RenderObject {
public:
    RenderTerminal(TerminalBuffer* buffer) : m_buffer(buffer) {}

    void paint(::acos::graphics::Renderer* renderer) override {
        if (!renderer || !m_buffer) return;

        // Draw solid background
        renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, TerminalBuffer::DEFAULT_BG);

        // Get console font for character drawing
        // If the console font isn't available, the software renderer fallback text drawing works
        u32 font_w = 8;
        u32 font_h = 16;

        usize cols = m_buffer->cols();
        usize rows = m_buffer->rows();

        for (usize r = 0; r < rows; r++) {
            i32 y = m_rect.y + static_cast<i32>(r * font_h);
            if (y >= m_rect.y + m_rect.h) break;

            for (usize c = 0; c < cols; c++) {
                i32 x = m_rect.x + static_cast<i32>(c * font_w);
                if (x >= m_rect.x + m_rect.w) break;

                Cell cell = m_buffer->get_cell(c, r);

                // Draw cell background if it differs from default
                if (cell.bg != TerminalBuffer::DEFAULT_BG) {
                    renderer->fill_rect(x, y, font_w, font_h, cell.bg);
                }

                // If reverse video flag is set, swap bg and fg
                u32 draw_fg = cell.fg;
                if (cell.flags & 4) {
                    draw_fg = cell.bg;
                    renderer->fill_rect(x, y, font_w, font_h, cell.fg);
                }

                // Draw character
                if (cell.ch != ' ' && cell.ch != '\0') {
                    char str[2] = {cell.ch, '\0'};
                    renderer->draw_text(str, x, y, draw_fg);
                }
            }
        }

        // Draw cursor block
        usize cc = m_buffer->cursor_col();
        usize cr = m_buffer->cursor_row();
        if (cc < cols && cr < rows) {
            i32 cx = m_rect.x + static_cast<i32>(cc * font_w);
            i32 cy = m_rect.y + static_cast<i32>(cr * font_h);
            renderer->fill_rect(cx, cy, font_w, font_h, TerminalBuffer::DEFAULT_FG);

            Cell cell = m_buffer->get_cell(cc, cr);
            if (cell.ch != ' ' && cell.ch != '\0') {
                char str[2] = {cell.ch, '\0'};
                renderer->draw_text(str, cx, cy, TerminalBuffer::DEFAULT_BG);
            }
        }
    }

    void perform_layout(gui::BoxConstraints constraints) override {
        m_rect.w = 600;
        m_rect.h = 360;
        gui::Size size = constraints.constrain({m_rect.w, m_rect.h});
        m_rect.w = size.w;
        m_rect.h = size.h;
    }

private:
    TerminalBuffer* m_buffer;
};

TerminalView::TerminalView() : m_buffer(), m_session(&m_buffer) {
    m_rect = {0, 0, 600, 360};
    m_session.start(on_session_output, this);
}

TerminalView::~TerminalView() {}

gui::Ref<gui::RenderObject> TerminalView::create_render_object() {
    return gui::UIContext::get().region().alloc<RenderTerminal>(&m_buffer);
}

void TerminalView::update_render_object(gui::Ref<gui::RenderObject> render_object) {
    gui::Widget::update_render_object(render_object);
}

void TerminalView::on_session_output(void* arg) {
    auto* view = static_cast<TerminalView*>(arg);
    view->trigger_redraw();
}

void TerminalView::trigger_redraw() {
    set_paint_dirty();
}

void TerminalView::on_event(gui::Event& event) {
    const auto& raw = event.raw;

    if (raw.type == InputType::Keyboard && raw.value == 1) { // Key Pressed
        VirtualKey vk = static_cast<VirtualKey>(raw.code);
        bool shift = (raw.flags & ModifierFlags::Shift) != 0;
        bool ctrl = (raw.flags & ModifierFlags::Ctrl) != 0;

        char seq[8];
        usize seq_len = 0;

        if (vk >= VirtualKey::A && vk <= VirtualKey::Z) {
            char base = 'a' + (static_cast<u32>(vk) - static_cast<u32>(VirtualKey::A));
            if (ctrl) {
                // Control combinations (e.g. Ctrl+C = 0x03)
                seq[0] = base - 'a' + 1;
                seq_len = 1;
            } else if (shift) {
                seq[0] = base - 'a' + 'A';
                seq_len = 1;
            } else {
                seq[0] = base;
                seq_len = 1;
            }
        } else if (vk >= VirtualKey::Num0 && vk <= VirtualKey::Num9) {
            char num_base = '0' + (static_cast<u32>(vk) - static_cast<u32>(VirtualKey::Num0));
            if (shift) {
                // Shift number mappings
                static const char shifted[] = {')', '!', '@', '#', '$', '%', '^', '&', '*', '('};
                seq[0] = shifted[num_base - '0'];
                seq_len = 1;
            } else {
                seq[0] = num_base;
                seq_len = 1;
            }
        } else {
            // Special keys
            switch (vk) {
                case VirtualKey::Enter:
                    seq[0] = '\n';
                    seq_len = 1;
                    break;
                case VirtualKey::Space:
                    seq[0] = ' ';
                    seq_len = 1;
                    break;
                case VirtualKey::Backspace:
                    seq[0] = '\b';
                    seq_len = 1;
                    break;
                case VirtualKey::Tab:
                    seq[0] = '\t';
                    seq_len = 1;
                    break;
                case VirtualKey::Up:
                    ::memcpy(seq, "\033[A", 3);
                    seq_len = 3;
                    break;
                case VirtualKey::Down:
                    ::memcpy(seq, "\033[B", 3);
                    seq_len = 3;
                    break;
                case VirtualKey::Right:
                    ::memcpy(seq, "\033[C", 3);
                    seq_len = 3;
                    break;
                case VirtualKey::Left:
                    ::memcpy(seq, "\033[D", 3);
                    seq_len = 3;
                    break;
                case VirtualKey::Home:
                    ::memcpy(seq, "\033[H", 3);
                    seq_len = 3;
                    break;
                case VirtualKey::End:
                    ::memcpy(seq, "\033[F", 3);
                    seq_len = 3;
                    break;
                case VirtualKey::Delete:
                    ::memcpy(seq, "\033[3~", 4);
                    seq_len = 4;
                    break;
                case VirtualKey::Minus:
                    seq[0] = shift ? '_' : '-';
                    seq_len = 1;
                    break;
                case VirtualKey::Equals:
                    seq[0] = shift ? '+' : '=';
                    seq_len = 1;
                    break;
                case VirtualKey::LBracket:
                    seq[0] = shift ? '{' : '[';
                    seq_len = 1;
                    break;
                case VirtualKey::RBracket:
                    seq[0] = shift ? '}' : ']';
                    seq_len = 1;
                    break;
                case VirtualKey::Semicolon:
                    seq[0] = shift ? ':' : ';';
                    seq_len = 1;
                    break;
                case VirtualKey::Quote:
                    seq[0] = shift ? '"' : '\'';
                    seq_len = 1;
                    break;
                case VirtualKey::Backtick:
                    seq[0] = shift ? '~' : '`';
                    seq_len = 1;
                    break;
                case VirtualKey::Backslash:
                    seq[0] = shift ? '|' : '\\';
                    seq_len = 1;
                    break;
                case VirtualKey::Comma:
                    seq[0] = shift ? '<' : ',';
                    seq_len = 1;
                    break;
                case VirtualKey::Period:
                    seq[0] = shift ? '>' : '.';
                    seq_len = 1;
                    break;
                case VirtualKey::Slash:
                    seq[0] = shift ? '?' : '/';
                    seq_len = 1;
                    break;
                default:
                    break;
            }
        }

        if (seq_len > 0) {
            m_session.write_input(seq, seq_len);
            event.stop_propagation();
        }
    }
}

} // namespace acos::apps
