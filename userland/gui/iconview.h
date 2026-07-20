#pragma once
#include "widget.h"
#include "icon.h"

namespace acos::gui::widgets {

class IconView : public Widget {
public:
    IconView();
    ~IconView() override;

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    void add_icon(IconType type, const char* label, void (*callback)(void*));

private:
    struct IconItem {
        IconType type;
        const char* label;
        void (*callback)(void*);
    };
    IconItem m_icons[16];
    usize m_count;
};

class RenderIconView : public RenderObject {
public:
    RenderIconView();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;
};

} // namespace acos::gui::widgets
