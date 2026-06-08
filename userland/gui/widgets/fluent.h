#pragma once
#include "../core/ref.h"
#include "../core/style.h"
#include "../text.h"
#include "../button.h"
#include "../core/flex.h"
#include "../core/stack.h"
#include "../core/grid.h"
#include "../core/context.h"
#include "../core/color.h"
#include "../panel.h"
#include "../listview.h"
#include "../progressbar.h"
#include "../graph.h"
#include "../badge.h"
#include "../icon.h"

namespace acos::gui {

template <typename T>
class FluentRef : public Ref<T> {
public:
    using Ref<T>::Ref;
    FluentRef(const Ref<T>& other) : Ref<T>(other) {}

    FluentRef<T>& background(u32 color) { if (this->is_valid()) this->operator->()->set_background_color(color); return *this; }
    FluentRef<T>& radius(u32 r) { if (this->is_valid()) this->operator->()->radius(r); return *this; }
    FluentRef<T>& border(u32 color, u32 width) { if (this->is_valid()) { this->operator->()->set_border_color(color); this->operator->()->set_border_width(width); } return *this; }
    FluentRef<T>& padding(u32 p) { if (this->is_valid()) this->operator->()->padding(p); return *this; }
    FluentRef<T>& padding(u32 top, u32 right, u32 bottom, u32 left) { if (this->is_valid()) this->operator->()->padding(top, right, bottom, left); return *this; }
    FluentRef<T>& margin(u32 m) { if (this->is_valid()) this->operator->()->margin(m); return *this; }
    FluentRef<T>& margin(u32 top, u32 right, u32 bottom, u32 left) { if (this->is_valid()) this->operator->()->margin(top, right, bottom, left); return *this; }
    FluentRef<T>& preferred_size(i32 w, i32 h) { if (this->is_valid()) this->operator->()->preferred_size(w, h); return *this; }
    FluentRef<T>& preferred_width(i32 w) { if (this->is_valid()) this->operator->()->preferred_width(w); return *this; }
    FluentRef<T>& preferred_height(i32 h) { if (this->is_valid()) this->operator->()->preferred_height(h); return *this; }
    FluentRef<T>& flex_grow(u32 factor) { if (this->is_valid()) this->operator->()->flex_grow(factor); return *this; }
    FluentRef<T>& elevation(u32 e) { if (this->is_valid()) this->operator->()->elevation(e); return *this; }
    FluentRef<T>& opacity(float o) { if (this->is_valid()) this->operator->()->opacity(o); return *this; }
    FluentRef<T>& position(Position pos) { if (this->is_valid()) this->operator->()->position(pos); return *this; }
    FluentRef<T>& anchor_top(i32 v) { if (this->is_valid()) this->operator->()->anchor_top(v); return *this; }
    FluentRef<T>& anchor_right(i32 v) { if (this->is_valid()) this->operator->()->anchor_right(v); return *this; }
    FluentRef<T>& anchor_bottom(i32 v) { if (this->is_valid()) this->operator->()->anchor_bottom(v); return *this; }
    FluentRef<T>& anchor_left(i32 v) { if (this->is_valid()) this->operator->()->anchor_left(v); return *this; }
    FluentRef<T>& fixed(i32 top = -1, i32 right = -1, i32 bottom = -1, i32 left = -1) { if (this->is_valid()) this->operator->()->fixed(top, right, bottom, left); return *this; }
};

class TextRef : public FluentRef<widgets::Text> {
public:
    using FluentRef<widgets::Text>::FluentRef; TextRef(const Ref<widgets::Text>& other) : FluentRef<widgets::Text>(other) {}
    TextRef& text(const char* t) { if (this->is_valid()) this->operator->()->set_text(t); return *this; }
    TextRef& color(u32 c) { if (this->is_valid()) this->operator->()->set_text_color(c); return *this; }
    TextRef& border(u32 color, u32 width) { if (this->is_valid()) { this->operator->()->set_border_color(color); this->operator->()->set_border_width(width); } return *this; }
    TextRef& font_size(u32 s) { if (this->is_valid()) this->operator->()->set_font_size(s); return *this; }
    TextRef& alignment(widgets::TextAlignment a) { if (this->is_valid()) this->operator->()->set_alignment(a); return *this; }
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
    ContainerRef<T>& child(Ref<Widget> c) { if (this->is_valid()) this->operator->()->add_child(c); return *this; }
};

class ColumnRef : public ContainerRef<widgets::Column> {
public:
    using ContainerRef<widgets::Column>::ContainerRef;
    ColumnRef& spacing(i32 s) { if (this->is_valid()) this->operator->()->spacing(s); return *this; }
    ColumnRef& add_child(Ref<Widget> c) { if (this->is_valid()) this->operator->()->add_child(c); return *this; }
    ColumnRef& main_axis_alignment(MainAxisAlignment a) { if (this->is_valid()) this->operator->()->main_axis_alignment(a); return *this; }
    ColumnRef& cross_axis_alignment(CrossAxisAlignment a) { if (this->is_valid()) this->operator->()->cross_axis_alignment(a); return *this; }
    ColumnRef& preferred_height(i32 h) { if (this->is_valid()) this->operator->()->preferred_height(h); return *this; }
    ColumnRef& flex_grow(u32 f) { if (this->is_valid()) this->operator->()->flex_grow(f); return *this; }
};

class RowRef : public ContainerRef<widgets::Row> {
public:
    using ContainerRef<widgets::Row>::ContainerRef;
    RowRef& spacing(i32 s) { if (this->is_valid()) this->operator->()->spacing(s); return *this; }
    RowRef& add_child(Ref<Widget> c) { if (this->is_valid()) this->operator->()->add_child(c); return *this; }
    RowRef& main_axis_alignment(MainAxisAlignment a) { if (this->is_valid()) this->operator->()->main_axis_alignment(a); return *this; }
    RowRef& cross_axis_alignment(CrossAxisAlignment a) { if (this->is_valid()) this->operator->()->cross_axis_alignment(a); return *this; }
    RowRef& preferred_height(i32 h) { if (this->is_valid()) this->operator->()->preferred_height(h); return *this; }
    RowRef& preferred_width(i32 w) { if (this->is_valid()) this->operator->()->preferred_width(w); return *this; }
    RowRef& flex_grow(u32 f) { if (this->is_valid()) this->operator->()->flex_grow(f); return *this; }
};

class PanelRef : public ContainerRef<widgets::Panel> {
public:
    using ContainerRef<widgets::Panel>::ContainerRef;
    PanelRef& color(u32 c) { if (this->is_valid()) this->operator->()->set_background_color(c); return *this; }
    PanelRef& glass(bool g) { if (this->is_valid()) this->operator->()->set_glass(g); return *this; }
    PanelRef& on_click(void (*callback)(void*)) { if (this->is_valid()) this->operator->()->on_click(callback); return *this; }
};

class IconRef : public FluentRef<widgets::Icon> {
public:
    using FluentRef<widgets::Icon>::FluentRef;
    IconRef& type([[maybe_unused]] widgets::IconType t) { if (this->is_valid()) this->operator->(); /* type is set in constructor usually */ return *this; }
    IconRef& active(bool a) { if (this->is_valid()) this->operator->()->set_active(a); return *this; }
    IconRef& foreground(u32 color) { if (this->is_valid()) this->operator->()->set_foreground_color(color); return *this; }
    IconRef& size(i32 s) { if (this->is_valid()) this->operator->()->set_size(s); return *this; }
    IconRef& on_click(void (*callback)(void*)) { if (this->is_valid()) this->operator->()->on_click(callback); return *this; }

    // Explicitly return IconRef to avoid slicing to FluentRef<Icon>
    IconRef& background(u32 color) { if (this->is_valid()) this->operator->()->set_background_color(color); return *this; }
    IconRef& radius(u32 r) { if (this->is_valid()) this->operator->()->radius(r); return *this; }
};

class ProgressBarRef : public FluentRef<widgets::ProgressBar> {
public:
    using FluentRef<widgets::ProgressBar>::FluentRef;
    ProgressBarRef& value(float v) { if (this->is_valid()) this->operator->()->set_value(v); return *this; }
    ProgressBarRef& foreground(u32 color) { if (this->is_valid()) this->operator->()->set_foreground_color(color); return *this; }
};

class GraphRef : public FluentRef<widgets::Graph> {
public:
    using FluentRef<widgets::Graph>::FluentRef;
    GraphRef& value(float v) { if (this->is_valid()) this->operator->()->add_value(v); return *this; }
};

class BadgeRef : public FluentRef<widgets::Badge> {
public:
    using FluentRef<widgets::Badge>::FluentRef;
    BadgeRef& text(const char* t) { if (this->is_valid()) this->operator->()->set_text(t); return *this; }
};

class ListViewRef : public FluentRef<widgets::ListView> {
public:
    using FluentRef<widgets::ListView>::FluentRef;
    ListViewRef& item(const char* t) { if (this->is_valid()) this->operator->()->add_item(t); return *this; }
};

class StackRef : public ContainerRef<widgets::Stack> {
public:
    using ContainerRef<widgets::Stack>::ContainerRef;
};

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

inline PanelRef Panel() {
    return UIContext::get().region().alloc<widgets::Panel>();
}

inline IconRef Icon(widgets::IconType type) {
    return UIContext::get().region().alloc<widgets::Icon>(type);
}

inline ProgressBarRef ProgressBar() {
    return UIContext::get().region().alloc<widgets::ProgressBar>();
}

inline GraphRef Graph() {
    return UIContext::get().region().alloc<widgets::Graph>();
}

inline BadgeRef Badge(const char* t = nullptr) {
    return UIContext::get().region().alloc<widgets::Badge>(t);
}

inline ListViewRef ListView() {
    return UIContext::get().region().alloc<widgets::ListView>();
}

inline StackRef Stack() {
    return UIContext::get().region().alloc<widgets::Stack>();
}

} // namespace acos::gui
