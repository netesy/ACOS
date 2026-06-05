#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class GridView : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    GridView(u32 columns = 1);
    virtual ~GridView();


    void set_columns(u32 columns) { m_columns = columns; }
    void add_cell(const char* text);
    void set_header(u32 index, const char* title);

private:
    u32 m_columns;
    const char* m_headers[8];
    const char* m_cells[256];
    u32 m_cell_count;
};

} // namespace acos::gui::widgets
