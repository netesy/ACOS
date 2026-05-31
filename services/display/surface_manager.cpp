#include "surface_manager.h"
#include <kernel/memory/heap.h>

namespace acos::display {

SurfaceManager::SurfaceManager() : m_surface_count(0) {
    for (usize i = 0; i < MAX_SURFACES; i++) {
        m_surfaces[i].id = 0;
    }
}

SurfaceManager::~SurfaceManager() {
}

Surface* SurfaceManager::create_surface(u64 owner_pid, u32 width, u32 height, bool double_buffered) {
    if (m_surface_count >= MAX_SURFACES) return nullptr;

    for (usize i = 0; i < MAX_SURFACES; i++) {
        if (m_surfaces[i].id == 0) {
            m_surfaces[i].id = i + 1;
            m_surfaces[i].owner_pid = owner_pid;
            m_surfaces[i].width = width;
            m_surfaces[i].height = height;
            m_surfaces[i].double_buffered = double_buffered;

            // For now, use kmalloc since we are currently building this into the "kernel services" layer
            // as per the existing Makefile structure, although it's logically a service.
            m_surfaces[i].buffer = (u32*)acos::memory::kmalloc(width * height * sizeof(u32));
            if (double_buffered) {
                m_surfaces[i].back_buffer = (u32*)acos::memory::kmalloc(width * height * sizeof(u32));
            } else {
                m_surfaces[i].back_buffer = nullptr;
            }

            m_surface_count++;
            return &m_surfaces[i];
        }
    }
    return nullptr;
}

void SurfaceManager::destroy_surface(u64 id) {
    for (usize i = 0; i < MAX_SURFACES; i++) {
        if (m_surfaces[i].id == id) {
            acos::memory::kfree(m_surfaces[i].buffer);
            if (m_surfaces[i].back_buffer) {
                acos::memory::kfree(m_surfaces[i].back_buffer);
            }
            m_surfaces[i].id = 0;
            m_surface_count--;
            break;
        }
    }
}

Surface* SurfaceManager::get_surface(u64 id) {
    if (id == 0) return nullptr;
    for (usize i = 0; i < MAX_SURFACES; i++) {
        if (m_surfaces[i].id == id) return &m_surfaces[i];
    }
    return nullptr;
}

bool SurfaceManager::swap_buffers(u64 id) {
    Surface* surface = get_surface(id);
    if (!surface || !surface->double_buffered) return false;

    u32* temp = surface->buffer;
    surface->buffer = surface->back_buffer;
    surface->back_buffer = temp;
    return true;
}

} // namespace acos::display
