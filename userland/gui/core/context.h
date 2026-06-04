#pragma once
#include "region.h"
#include "focus_manager.h"
#include "event_dispatcher.h"

namespace acos::gui {

class UIContext {
public:
    UIContext();
    ~UIContext();

    static UIContext& get();

    Region& region() { return m_main_region; }
    FocusManager& focus_manager() { return m_focus_manager; }
    EventDispatcher& event_dispatcher() { return m_event_dispatcher; }

    void paint(acos::graphics::Renderer* renderer);

private:
    Region m_main_region;
    FocusManager m_focus_manager;
    EventDispatcher m_event_dispatcher;
    static UIContext* s_instance;
};

} // namespace acos::gui
