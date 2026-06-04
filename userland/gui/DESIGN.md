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

## Phase 3: Event Dispatching and Focus Management

### 1. Hit Testing
A recursive process to find the deepest widget in the tree that contains a given point.
- `Widget::hit_test(x, y)`: Returns the deepest child at the coordinates, or itself if it contains the point but none of its children do.

### 2. Event Routing (Capture & Bubble)
Events follow a standard routing path:
1. **Capture Phase**: Event travels from the root down to the target widget.
2. **At Target**: Event is processed by the target widget.
3. **Bubble Phase**: Event travels from the target widget back up to the root.

Widgets can intercept events at any phase and stop propagation.

### 3. Focus Manager
Centralizes focus handling across the UI.
- Maintains a reference to the currently focused widget.
- Handles focus transitions (e.g., Tab navigation).
- Dispatches focus-in and focus-out events.

### 4. Event Dispatcher
The entry point for all system events.
- Performs hit testing for mouse events to find the target.
- Uses the focused widget as the target for keyboard events.
- Executes the Capture/Bubble routing logic.

## Class Diagrams (Proposed - Phase 4)

```cpp
namespace acos::gui {

struct Size {
    i32 w, h;
};

struct BoxConstraints {
    i32 min_w, max_w;
    i32 min_h, max_h;

    static BoxConstraints loose(i32 max_w, i32 max_h);
    static BoxConstraints tight(i32 w, i32 h);
};

// In Widget class:
// virtual Size layout(BoxConstraints constraints);

class Flex : public Widget {
    // Axis: Horizontal/Vertical
    // MainAxisAlignment
    // CrossAxisAlignment
public:
    Size layout(BoxConstraints constraints) override;
};

}
```

## Class Diagrams (Proposed - Phase 3)

```cpp
namespace acos::gui {

enum class EventPhase {
    Capture,
    Target,
    Bubble
};

struct Event {
    acos::input::InputEvent raw;
    EventPhase phase;
    Ref<Widget> target;
    bool handled;

    void stop_propagation() { handled = true; }
};

class FocusManager {
    Ref<Widget> m_focused;
public:
    void set_focus(Ref<Widget> widget);
    Ref<Widget> focused() const;
};

class EventDispatcher {
public:
    void dispatch(const acos::input::InputEvent& raw, Ref<Widget> root);
private:
    Ref<Widget> hit_test(Ref<Widget> root, i32 x, i32 y);
};

}
```

## Ownership Diagram (Phase 3)

```
UIContext
 ├── Region (Owns Widgets)
 ├── FocusManager (Holds Ref<Widget>)
 └── EventDispatcher
```

## Phase 4: Constraint Layout Engine

### 1. BoxConstraints
Inspired by Flutter, ACOS uses a "Constraints go down, sizes go up" model.
- `BoxConstraints`: Defines minimum and maximum width and height.
- `Size`: A simple width and height pair.

### 2. Layout Flow
1. **Parent** passes `BoxConstraints` to **Child**.
2. **Child** determines its own **Size** within those constraints.
3. **Child** passes its **Size** back to **Parent**.
4. **Parent** uses the child's size to position the child and determine its own size.

### 3. Layout Widgets
- **Row/Column (Flex)**: Distributes children along a primary axis. Supports flexible sizing (expanding to fill space).
- **Stack**: Layers children on top of each other.
- **Grid**: Arranges children in a fixed or dynamic grid.

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
