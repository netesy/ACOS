#pragma once
#include "region.h"
#include "focus_manager.h"
#include "event_dispatcher.h"
#include "render_object.h"

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
    void set_root_render_object(Ref<RenderObject> root) { m_root_render_object = root; }

private:
    Region m_main_region;
    FocusManager m_focus_manager;
    EventDispatcher m_event_dispatcher;
    Ref<RenderObject> m_root_render_object;
    static UIContext* s_instance;
};

} // namespace acos::gui
