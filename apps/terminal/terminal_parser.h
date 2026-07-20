#pragma once
#include <acos/types.h>
#include "terminal_buffer.h"

namespace acos::apps {

class TerminalParser {
public:
    TerminalParser(TerminalBuffer* buffer);
    ~TerminalParser();

    void write(const char* data, usize len);

private:
    enum State {
        Normal,
        Escape,
        CSI
    };

    void process_char(char c);
    void handle_csi_command(char final_char);
    void parse_sgr();

    TerminalBuffer* m_buffer;
    State m_state;

    // SGR styles
    u32 m_fg;
    u32 m_bg;
    u8 m_flags;

    // CSI parameters
    static constexpr usize MAX_PARAMS = 16;
    int m_params[MAX_PARAMS];
    usize m_param_count;
    bool m_param_has_digit;
};

} // namespace acos::apps
