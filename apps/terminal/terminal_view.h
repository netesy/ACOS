#pragma once
#include <userland/gui/widget.h>
#include "terminal_buffer.h"
#include "terminal_session.h"

namespace acos::apps {

class TerminalView : public gui::Widget {
public:
    TerminalView();
    ~TerminalView() override;

    gui::Ref<gui::RenderObject> create_render_object() override;
    void update_render_object(gui::Ref<gui::RenderObject> render_object) override;

    void on_event(gui::Event& event) override;

    TerminalBuffer* buffer() { return &m_buffer; }
    TerminalSession* session() { return &m_session; }

    void trigger_redraw();

private:
    static void on_session_output(void* arg);

    TerminalBuffer m_buffer;
    TerminalSession m_session;
};

} // namespace acos::apps
