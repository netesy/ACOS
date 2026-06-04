# ACOS Modern GUI Framework: Comprehensive Architecture Specification

## Executive Summary
The ACOS Modern GUI Framework (AMGF) is a high-performance, retained-mode UI framework designed for the ACOS operating system. It eliminates common bottlenecks in traditional UI toolkits by employing a decoupled architecture (Widget/Layout/Render), region-based memory management, and a reactive state model.

---

## 1. Memory Architecture & Performance
### Region-Based Allocation
AMGF avoids the overhead of general-purpose allocators and the complexity of reference counting.
- **Region**: A contiguous block of memory (Arena) owned by a `UIContext`.
- **Allocation**: Bump-pointer allocation for O(1) performance and perfect cache locality.
- **Deallocation**: The entire region is wiped when the context is destroyed.

### Generational References (`Ref<T>`)
To allow safe cross-references between objects in the region, we use Generational Handles.
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

---

## 2. UI Context
The `UIContext` provides the environment and lifecycle management for a UI tree. It manages memory via its internal `Region` and `ObjectPool`, and coordinates the system passes (build, layout, paint).

---

## 3. The Three Trees
AMGF maintains three distinct trees to separate concerns:

1.  **Widget Tree**: Immutable "blueprints". Rebuilt or updated frequently.
2.  **Layout Tree (`LayoutNode`)**: Handles geometric constraints and positioning.
3.  **Render Tree (`RenderObject`)**: Persistent objects that handle painting and hit testing.

### Layout Engine (Flutter-style)
- **Constraints**: `min_width, max_width, min_height, max_height`.
- **Flow**:
    1. Parent passes constraints to children.
    2. Children decide their size within those constraints.
    3. Parent positions children.

---

## 4. Event System
AMGF implements a three-phase event propagation model.
1.  **Capture Phase**: Event travels from root down to the target.
2.  **Target Phase**: Event is handled by the target widget.
3.  **Bubble Phase**: Event travels back up to the root.

---

## 5. Reactive State
State management uses a subscription model to minimize redraws.
```cpp
template<typename T>
class Signal {
    T m_value;
    List<Ref<Widget>> m_subscribers;
public:
    void set(UIContext* ctx, T value) {
        m_value = value;
        for(auto& w : m_subscribers) w->mark_dirty();
    }
};
```

---

## 6. Animation System
Animations are integrated into the `UIContext` scheduler.
```cpp
class Animation {
    void tick(UIContext* ctx, u64 now) {
        // Update property and mark widget dirty
    }
};
```

---

## 7. Styling & Fluent API
Styles are handled through a modifier pattern.
```cpp
Button("Save")
    .background(Color::Blue)
    .radius(8)
    .padding(12);
```

---

## 8. Final Implementation Notes
The framework has been fully integrated into the ACOS system, replacing the legacy GUI system. All system applications have been ported to this architecture.
