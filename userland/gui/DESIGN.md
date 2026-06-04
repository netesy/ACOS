# ACOS Modern GUI Framework Design

## Phase 1: Core Infrastructure

### 1. Region Ownership
A `Region` is a memory arena dedicated to UI object allocations.
- **Ownership**: The `Region` owns the memory of all widgets allocated within it. When a `Region` is destroyed, all its widgets are destroyed.
- **Allocation**: High-performance arena allocation.
- **Deallocation**: Can be done explicitly via `Ref<T>`, or implicitly by destroying the `Region`.

### 2. Generational References (Ref<T>)
`Ref<T>` is a smart handle used instead of raw pointers for `Widget` references.
- **Structure**: Contains an `index` and a `generation`.
- **Safety**: Prevents use-after-free. If a widget is destroyed and its slot is reused, the generation increments. Old `Ref<T>` instances will fail the generation check.
- **Performance**: Resolution is a simple array indexing and a comparison.

### 3. UIContext
The `UIContext` represents the global state of the UI system for a given application or window.
- **Responsibilities**:
    - Manages the primary `Region`.
    - Holds the `FocusManager`.
    - Coordinates event dispatching.
    - Manages the `Widget` tree root.

## Lifetime Management
- Widgets are always owned by a `Region`.
- Parent-child relationships use `Ref<T>`.
- The `UIContext` typically outlives the `Region` it manages for the current view.

## Phase 2: Widget Tree evolution

### 1. Dynamic Children
Instead of a fixed-size array, widgets will support a dynamic number of children. This will be implemented using a simple linked list or a dynamic array (if `acos::Vector` is available) of `Ref<Widget>`.

### 2. Dirty Tracking
To optimize rendering and layout, a dirty tracking system will be introduced.
- **Flags**: `LayoutDirty`, `PaintDirty`.
- **Propagation**: When a widget's state changes, it marks itself as dirty. Certain changes (like size) may also mark the parent as layout-dirty.
- **UIContext Integration**: The `UIContext` will maintain a list of dirty widgets to process during the next frame.

## Performance Implications
- **Memory Locality**: Widgets in the same `Region` are likely to be contiguous in memory, improving cache hits during tree traversals (layout, rendering).
- **Zero Fragmentation**: Arena-based allocation avoids the fragmentation issues of a general-purpose heap.
- **Fast Handle Resolution**: Resolving a `Ref<T>` to a pointer is nearly as fast as a raw pointer dereference.

---

## Class Diagrams (Proposed)

```cpp
namespace acos::gui {

template<typename T>
class Ref {
    u32 m_index;
    u32 m_generation;
public:
    T* operator->();
    bool is_valid() const;
};

class Region {
    struct Slot {
        u32 generation;
        alignas(16) u8 storage[256]; // Example fixed size for simple implementation
        bool occupied;
    };
    Vector<Slot> m_slots;
public:
    template<typename T, typename... Args>
    Ref<T> alloc(Args&&... args);
    void dealloc(u32 index);
};

class UIContext {
    Region m_main_region;
    Ref<Widget> m_root;
public:
    UIContext();
    Region& region() { return m_main_region; }
};

}
```
