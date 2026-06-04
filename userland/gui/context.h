#pragma once
#include "region.h"
#include "pool.h"
#include "ref.h"
#include "event.h"
#include "layout_node.h"
#include "render_object.h"

namespace acos::ui {

class Widget;
class FocusManager;
class AnimationManager;
class Theme;

class UIContext {
public:
    UIContext(usize region_size = 1024 * 1024);
    ~UIContext() = default;

    template<typename T, typename... Args>
    Ref<T> make(Args&&... args) {
        T* ptr = m_region.make<T>(static_cast<Args&&>(args)...);
        if (!ptr) return Ref<T>::null();
        u32 index = m_pool.store(ptr);
        return { index, m_pool.generation(index) };
    }

    ObjectPool& pool() { return m_pool; }
    Region& region() { return m_region; }

    Ref<RenderObject> render_root() { return m_render_root; }
    void set_render_root(Ref<RenderObject> root) { m_render_root = root; }

    Ref<LayoutNode> layout_root() { return m_layout_root; }
    void set_layout_root(Ref<LayoutNode> root) { m_layout_root = root; }

    FocusManager& focus_manager() { return *m_focus_manager; }
    AnimationManager& animation_manager() { return *m_animation_manager; }
    Theme& theme();

    void process_event(UIEvent& event);
    void update(u64 now);
    void perform_layout(Constraints constraints);
    void paint(acos::graphics::Renderer* renderer);

    void build_tree(Ref<Widget> root);
    void rebuild_dirty_widgets(Ref<Widget> root);

private:
    Region m_region;
    ObjectPool m_pool;
    EventDispatcher m_dispatcher;
    FocusManager* m_focus_manager;
    AnimationManager* m_animation_manager;
    Ref<RenderObject> m_render_root = Ref<RenderObject>::null();
    Ref<LayoutNode> m_layout_root = Ref<LayoutNode>::null();

    void build_recursive(Ref<Widget> widget, Ref<LayoutNode> parent_layout, Ref<RenderObject> parent_render);
};

template<typename T> T* Ref<T>::get(UIContext* ctx) const {
    return static_cast<T*>(ctx->pool().resolve(index, generation));
}

} // namespace acos::ui
