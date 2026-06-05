#pragma once
#include "core/ref.h"
#include "text.h"
#include "button.h"
#include "core/flex.h"
#include "core/stack.h"
#include "core/grid.h"
#include "core/context.h"
#include "core/color.h"

namespace acos::gui {

template <typename T>
class FluentRef : public Ref<T> {
public:
    using Ref<T>::Ref;
    FluentRef(const Ref<T>& other) : Ref<T>(other) {}

    FluentRef<T>& background(u32 color) { if (this->is_valid()) this->operator->()->background(color); return *this; }
    FluentRef<T>& radius(u32 r) { if (this->is_valid()) this->operator->()->radius(r); return *this; }
    FluentRef<T>& padding(u32 p) { if (this->is_valid()) this->operator->()->padding(p); return *this; }
    FluentRef<T>& elevation(u32 e) { if (this->is_valid()) this->operator->()->elevation(e); return *this; }
    FluentRef<T>& opacity(float o) { if (this->is_valid()) this->operator->()->opacity(o); return *this; }
};

class TextRef : public FluentRef<widgets::Text> {
public:
    using FluentRef<widgets::Text>::FluentRef; TextRef(const Ref<widgets::Text>& other) : FluentRef<widgets::Text>(other) {}
    TextRef& text(const char* t) { if (this->is_valid()) this->operator->()->text(t); return *this; }
    TextRef& color(u32 c) { if (this->is_valid()) this->operator->()->color(c); return *this; }
    TextRef& font_size(u32 s) { if (this->is_valid()) this->operator->()->font_size(s); return *this; }
};

class ButtonRef : public FluentRef<widgets::Button> {
public:
    using FluentRef<widgets::Button>::FluentRef; ButtonRef(const Ref<widgets::Button>& other) : FluentRef<widgets::Button>(other) {}
    ButtonRef& label(const char* l) { if (this->is_valid()) this->operator->()->label(l); return *this; }
    ButtonRef& on_click(void (*callback)(void*)) { if (this->is_valid()) this->operator->()->on_click(callback); return *this; }
};

template <typename T>
class ContainerRef : public FluentRef<T> {
public:
    using FluentRef<T>::FluentRef; ContainerRef(const Ref<T>& other) : FluentRef<T>(other) {}
    ContainerRef<T>& child(Ref<Widget> c) { if (this->is_valid()) this->operator->()->child(c); return *this; }
};

using ColumnRef = ContainerRef<widgets::Column>;
using RowRef = ContainerRef<widgets::Row>;

// Factory Functions
inline TextRef Text(const char* label = nullptr) {
    return UIContext::get().region().alloc<widgets::Text>(label);
}

inline ButtonRef Button(const char* label = nullptr) {
    return UIContext::get().region().alloc<widgets::Button>(label);
}

inline ColumnRef Column() {
    return UIContext::get().region().alloc<widgets::Column>();
}

inline RowRef Row() {
    return UIContext::get().region().alloc<widgets::Row>();
}

} // namespace acos::gui
