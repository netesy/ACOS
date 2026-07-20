#pragma once
#include <userland/gui/window_widget.h>
#include <userland/gui/textbox.h>
#include <userland/gui/textarea.h>
#include "terminal_view.h"

namespace acos::apps {

class Terminal : public gui::WindowWidget {
public:
    Terminal();
    ~Terminal() override;

private:
    gui::Ref<TerminalView> m_view;
};

} // namespace acos::apps
