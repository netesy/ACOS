# ACOS Modern GUI Framework: Comprehensive Architecture Specification

## Executive Summary
The ACOS Modern GUI Framework (AMGF) is a high-performance, retained-mode UI framework designed for the ACOS operating system. It eliminates common bottlenecks in traditional UI toolkits by employing a decoupled architecture (Widget/Layout/Render), region-based memory management, and a reactive state model.

---

## 1. Memory Architecture & Performance (Task 3, 13)
### Region-Based Allocation
AMGF avoids the overhead of general-purpose allocators and the complexity of reference counting (`shared_ptr`).
- **Region**: A contiguous block of memory (Arena) owned by a `UIContext`.
- **Allocation**: Bump-pointer allocation for O(1) performance and perfect cache locality.
- **Deallocation**: The entire region is wiped when the context or a specific scope is destroyed.

### Generational References (`Ref<T>`)
To allow safe cross-references between objects in the region (e.g., a widget keeping a reference to its parent or a sibling), we use Generational Handles.
```cpp
template<typename T>
struct Ref {
    u32 index;      // Index into the Object Pool
    u32 generation; // Generation counter to detect reuse

    T* get(UIContext* ctx) const {
        return ctx->pool().resolve<T>(index, generation);
    }
};
```
**Task 13 Analysis**:
- **Option C (Region + Ref)**:
    - *Memory Overhead*: 8 bytes per `Ref` vs 16 bytes for `shared_ptr`.
    - *Cache Locality*: Extremely high due to linear allocation.
    - *Traversal*: Fast, single pointer indirection after validation.
    - *Destruction*: O(1) for the whole tree.

---

## 2. UI Context (Task 1)
The `UIContext` provides the environment and lifecycle management for a UI tree.

```cpp
class UIContext {
public:
    UIContext(Region& region);

    // Factory methods
    template<typename T, typename... Args>
    Ref<T> make(Args&&... args);

    // Tree Roots
    Ref<Widget> root_widget() { return m_root; }
    Ref<RenderObject> render_root() { return m_render_root; }

    // Core Systems
    EventDispatcher& events() { return m_events; }
    FocusManager& focus() { return m_focus; }
    Scheduler& scheduler() { return m_scheduler; }

    // Lifecycle
    void rebuild_dirty_widgets();
    void layout(Constraints constraints);
    void paint(Renderer& renderer);

private:
    Region& m_region;
    ObjectPool m_pool;
    Ref<Widget> m_root;
    Ref<RenderObject> m_render_root;
    // ... system instances
};
```

---

## 3. The Three Trees (Task 2, 5, 6)
AMGF maintains three distinct trees to separate concerns:

1.  **Widget Tree**: Immutable "blueprints". Rebuilt frequently.
2.  **Layout Tree (`LayoutNode`)**: Handles geometric constraints and positioning.
3.  **Render Tree (`RenderObject`)**: Persistent objects that handle painting and hit testing.

### Widget Tree
```cpp
class Widget {
public:
    virtual Ref<RenderObject> create_render_object(UIContext* ctx) = 0;
    virtual void update_render_object(UIContext* ctx, Ref<RenderObject> obj) = 0;

    // Fluent Modifiers
    Widget& padding(f32 p);
    Widget& background(Color c);
};
```

### Layout Engine (Flutter-style)
- **Constraints**: `min_width, max_width, min_height, max_height`.
- **Flow**:
    1. Parent passes constraints to children.
    2. Children decide their size within those constraints.
    3. Parent positions children.

---

## 4. Event System (Task 4)
AMGF implements a three-phase event propagation model.

1.  **Capture Phase**: Event travels from root down to the target.
2.  **Target Phase**: Event is handled by the target widget.
3.  **Bubble Phase**: Event travels back up to the root.

```cpp
struct UIEvent {
    enum Type { Mouse, Key, Scroll, Focus };
    Type type;
    bool consumed = false;
    void consume() { consumed = true; }
};
```

---

## 5. Reactive State (Task 8)
State management uses a subscription model to minimize redraws.

```cpp
template<typename T>
class State {
    T m_value;
    Vector<Ref<Widget>> m_subscribers;

public:
    void set(T value) {
        m_value = value;
        for(auto& w : m_subscribers) w->mark_dirty();
    }
};
```

---

## 6. Animation System (Task 9)
Animations are integrated into the `UIContext` scheduler.

```cpp
class Animation {
    f32 m_start, m_end;
    u64 m_duration;
    Easing m_easing;

    void tick(u64 now) {
        f32 progress = (now - m_start_time) / (f32)m_duration;
        m_current = lerp(m_start, m_end, m_easing(progress));
    }
};
```

---

## 7. Styling & Fluent API (Task 7, 10)
Styles are handled through a modifier pattern that generates a `Style` object associated with a widget.

```cpp
Button("Save")
    .background(Color::Blue) // Returns a modified Widget reference
    .radius(8)
    .padding(12);
```

---

## 8. Windowing & Compositing (Task 11, 12)
- **Compositor**: Blends multiple `WindowSurfaces`. Supports hardware-accelerated transparency and blur.
- **Window**: Each window owns a `UIContext`.

---

## 9. Migration & Implementation Strategy
1.  **Phase 1**: Core Infrastructure (`Region`, `Ref`, `Pool`).
2.  **Phase 2**: Widget/RenderObject Base Classes.
3.  **Phase 3**: Basic Layout (Row, Column).
4.  **Phase 4**: Event Dispatcher.
5.  **Phase 5**: Graphics Port (Renderer integration).
6.  **Phase 6**: Shell Port (Taskbar rewrite).

---

## 10. Final Recommendation
AMGF should be implemented as `userland/libui` to clearly distinguish it from the legacy system. The primary focus should be on the **Region-based memory model**, as it provides the most significant performance advantage for a desktop environment running on a custom microkernel.

## 11. Final Implementation Notes
The legacy `acos::gui` system has been completely replaced by the modern `acos::ui` framework. All existing applications (Terminal, Settings, File Manager, Shell) have been ported to the new header structure.

The framework now uses:
- **Region-based allocation** for zero-fragmentation and O(1) alloc/dealloc.
- **Generational References (`Ref<T>`)** for safe object tracking.
- **Decoupled trees** for Widgets, Layout, and Rendering.
- **Fluent Modifier API** (e.g., `Button().radius(8).background(Color::Blue)`).

This architecture provides the scalability required for the ACOS desktop environment while maintaining the performance characteristics of a freestanding microkernel OS.
