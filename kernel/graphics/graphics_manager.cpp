#include <kernel/graphics/graphics_manager.h>
#include <kernel/graphics/font_manager.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/hal/serial.h>

namespace acos::graphics {

namespace {

class BootFramebufferDisplay final : public DisplayDevice {
public:
    BootFramebufferDisplay() : m_framebuffer(nullptr), m_initialized(false) {}

    void attach(Framebuffer* framebuffer) {
        m_framebuffer = framebuffer;
        m_initialized = framebuffer != nullptr;
    }

    bool initialize() override {
        return m_initialized && m_framebuffer != nullptr;
    }

    Framebuffer* get_framebuffer() override {
        return m_framebuffer;
    }

    u32 width() const override {
        return m_framebuffer ? m_framebuffer->width() : 0;
    }

    u32 height() const override {
        return m_framebuffer ? m_framebuffer->height() : 0;
    }

private:
    Framebuffer* m_framebuffer;
    bool m_initialized;
};

alignas(Framebuffer) static u8 g_boot_framebuffer_storage[sizeof(Framebuffer)];
alignas(BootFramebufferDisplay) static u8 g_boot_display_storage[sizeof(BootFramebufferDisplay)];
static Framebuffer* g_boot_framebuffer = nullptr;
static BootFramebufferDisplay* g_boot_display = nullptr;

BootFramebufferDisplay* boot_display() {
    if (!g_boot_display) {
        g_boot_display = new (g_boot_display_storage) BootFramebufferDisplay();
    }
    return g_boot_display;
}

bool valid_boot_framebuffer(FramebufferInfo* info) {
    return info && info->base != 0 && info->width != 0 && info->height != 0 && info->pitch != 0;
}

} // namespace

DisplayDevice* GraphicsManager::g_displays[4];
u32 GraphicsManager::g_display_count = 0;

void GraphicsManager::register_display(DisplayDevice* display) {
    if (display && g_display_count < 4) {
        g_displays[g_display_count++] = display;
    }
}

DisplayDevice* GraphicsManager::primary_display() {
    if (g_display_count > 0) return g_displays[0];
    return nullptr;
}

void GraphicsManager::init() {
    init(nullptr);
}

void GraphicsManager::init(FramebufferInfo* boot_framebuffer) {
    g_display_count = 0;
    for (u32 i = 0; i < 4; ++i) {
        g_displays[i] = nullptr;
    }

    acos::hal::serial_print("GraphicsManager::init - start\n");

    if (!valid_boot_framebuffer(boot_framebuffer)) {
        acos::hal::serial_print("GraphicsManager::init - invalid boot framebuffer\n");
        boot_display()->attach(nullptr);
        g_boot_framebuffer = nullptr;
        return;
    }

    g_boot_framebuffer = new (g_boot_framebuffer_storage) Framebuffer(
        boot_framebuffer->base,
        boot_framebuffer->size,
        boot_framebuffer->width,
        boot_framebuffer->height,
        boot_framebuffer->pitch,
        boot_framebuffer->bpp);
    boot_display()->attach(g_boot_framebuffer);
    register_display(boot_display());

    acos::hal::serial_print("GraphicsManager::init - calling FontManager::initialize\n");
    FontManager::initialize();
    acos::hal::serial_print("GraphicsManager::init - end\n");
}

} // namespace acos::graphics
