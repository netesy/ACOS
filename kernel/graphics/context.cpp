#include <kernel/graphics/context.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>

namespace acos::graphics {

GraphicsContext::GraphicsContext(TargetType type, u64 target_handle)
    : m_target_type(type), m_target_handle(target_handle), m_clip_rect{0, 0, 0, 0}, m_clip_enabled(false) {}

namespace {

struct ResolvedTarget {
    Framebuffer* fb = nullptr;
    Surface* surface = nullptr;
};

ResolvedTarget resolve_target(GraphicsContext::TargetType target_type, u64 target_handle) {
    ResolvedTarget result;
    auto* current_thr = scheduler::current_thread();
    if (!current_thr || !current_thr->parent) return result;
    auto* current = current_thr->parent;

    auto* entry = current->get_handle(target_handle);
    if (!entry) return result;

    if (target_type == GraphicsContext::TargetType::Display && entry->kind == scheduler::ResourceKind::GraphicsDisplay) {
        auto* display = static_cast<DisplayDevice*>(entry->object);
        if (display) {
            result.fb = display->get_framebuffer();
        }
    } else if (target_type == GraphicsContext::TargetType::Surface && entry->kind == scheduler::ResourceKind::GraphicsSurface) {
        auto* surface = static_cast<Surface*>(entry->object);
        if (surface && surface->is_valid()) {
            result.surface = surface;
        }
    }
    return result;
}

} // namespace

void GraphicsContext::put_pixel(u32 x, u32 y, u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.draw_pixel(x, y, color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(x, y, 1, 1);
    }
}

void GraphicsContext::draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.draw_line(x1, y1, x2, y2, color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        i32 min_x = x1 < x2 ? x1 : x2;
        i32 min_y = y1 < y2 ? y1 : y2;
        i32 max_x = x1 > x2 ? x1 : x2;
        i32 max_y = y1 > y2 ? y1 : y2;
        tgt.surface->dirty_region().invalidate(min_x, min_y, max_x - min_x + 1, max_y - min_y + 1);
    }
}

void GraphicsContext::draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.draw_rect(x, y, w, h, color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(x, y, w, h);
    }
}

void GraphicsContext::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.fill_rect(x, y, w, h, color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(x, y, w, h);
    }
}

void GraphicsContext::draw_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.draw_circle(cx, cy, radius, color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(cx - radius, cy - radius, radius * 2 + 1, radius * 2 + 1);
    }
}

void GraphicsContext::fill_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.fill_circle(cx, cy, radius, color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(cx - radius, cy - radius, radius * 2 + 1, radius * 2 + 1);
    }
}

void GraphicsContext::blit(u32 dx, u32 dy, Surface* src_surface, u32 sx, u32 sy, u32 sw, u32 sh) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.blit(dx, dy, src_surface, sx, sy, sw, sh);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(dx, dy, sw, sh);
    }
}

void GraphicsContext::clear(u32 color) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.clear(color);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(0, 0, width(), height());
    }
}

void GraphicsContext::copy_rect(u32 dx, u32 dy, u32 sx, u32 sy, u32 w, u32 h) {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return;

    Renderer renderer(tgt.fb, tgt.surface);
    if (m_clip_enabled) renderer.set_clip_rect(m_clip_rect);

    renderer.copy_rect(dx, dy, sx, sy, w, h);
    if (m_target_type == TargetType::Surface && tgt.surface) {
        tgt.surface->dirty_region().invalidate(dx, dy, w, h);
    }
}

void GraphicsContext::set_clip_rect(const ClipRect& rect) {
    m_clip_rect = rect;
    m_clip_enabled = true;
}

void GraphicsContext::clear_clip_rect() {
    m_clip_enabled = false;
}

u32 GraphicsContext::width() const {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return 0;
    Renderer renderer(tgt.fb, tgt.surface);
    return renderer.width();
}

u32 GraphicsContext::height() const {
    ResolvedTarget tgt = resolve_target(m_target_type, m_target_handle);
    if (!tgt.fb && !tgt.surface) return 0;
    Renderer renderer(tgt.fb, tgt.surface);
    return renderer.height();
}

} // namespace acos::graphics
