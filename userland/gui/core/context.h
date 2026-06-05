#pragma once
#include "region.h"
#include "focus_manager.h"
#include "event_dispatcher.h"
#include "render_object.h"
#include "animation.h"
#include "compositor_engine.h"

namespace acos::gui {

class UIContext {
public:
    UIContext();
    ~UIContext();

    static UIContext& get();

    Region& region() { return m_main_region; }
    FocusManager& focus_manager() { return m_focus_manager; }
    EventDispatcher& event_dispatcher() { return m_event_dispatcher; }
    AnimationController& animation_controller() { return m_animation_controller; }
    void set_compositor(SoftwareCompositor* compositor) { m_compositor = compositor; }

    void paint(acos::graphics::Renderer* renderer);
    void update(u64 delta_ms);
    void set_root_render_object(Ref<RenderObject> root) { m_root_render_object = root; }
    void set_root(Ref<Widget> root) { m_root = root; }

private:
    void sync_render_tree(Ref<Widget> widget, Ref<RenderObject>& render_object);

    Region m_main_region;
    FocusManager m_focus_manager;
    EventDispatcher m_event_dispatcher;
    AnimationController m_animation_controller;
    Ref<Widget> m_root;
    Ref<RenderObject> m_root_render_object;
    SoftwareCompositor* m_compositor = nullptr;
    static UIContext* s_instance;
};

} // namespace acos::gui
