#include "taskbar.h"
#include "context.h"
#include "render_object.h"
#include "basic_widgets.h"
#include "text.h"
#include "color.h"
namespace acos::shell {
class TaskbarRenderObject : public ui::RenderObject {
public:
    void paint(ui::UIContext* ctx, acos::graphics::Renderer* renderer, ui::Position offset) override {
        ui::Position pos = { offset.x + m_position.x, offset.y + m_position.y };
        renderer->draw_rect(pos.x, pos.y, m_size.w, m_size.h, 0xCC1A1A1B);
        ui::Ref<ui::RenderObject> child = first_child();
        while (!child.is_null()) {
            ui::RenderObject* child_obj = child.get(ctx);
            child_obj->paint(ctx, renderer, pos);
            child = child_obj->next_sibling();
        }
    }
};
Taskbar::Taskbar() {}
void Taskbar::update_clock() {}
ui::Ref<ui::LayoutNode> Taskbar::create_layout_node(ui::UIContext* ctx) { return ctx->make<ui::RowLayoutNode>(); }
ui::Ref<ui::RenderObject> Taskbar::create_render_object(ui::UIContext* ctx) { return ctx->make<TaskbarRenderObject>(); }
}
