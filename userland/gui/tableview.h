#pragma once
#include "widget.h"
#include "core/render_object.h"

namespace acos::gui::widgets {

class TableView : public Widget {
public:
    TableView();
    ~TableView();

    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    void set_columns(const char** cols, usize count);
    void set_data(const char* data[10][5], usize rows, usize cols);

private:
    const char* m_columns[5];
    usize m_col_count;

    const char* m_data[10][5];
    usize m_row_count;
};

class RenderTableView : public RenderObject {
public:
    RenderTableView();
    void paint(::acos::graphics::Renderer* renderer) override;
    void perform_layout(BoxConstraints constraints) override;

    void set_columns(const char** cols, usize count);
    void set_data(const char* data[10][5], usize rows, usize cols);

private:
    const char* m_columns[5];
    usize m_col_count;

    const char* m_data[10][5];
    usize m_row_count;
};

} // namespace acos::gui::widgets
