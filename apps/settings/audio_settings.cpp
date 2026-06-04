#include "audio_settings.h"
#include "context.h"

namespace acos::apps {

AudioSettings::AudioSettings() : m_title("Audio Settings") {
}

ui::Ref<ui::LayoutNode> AudioSettings::create_layout_node(ui::UIContext* ctx) { return ctx->make<ui::LeafLayoutNode>(); }
ui::Ref<ui::RenderObject> AudioSettings::create_render_object(ui::UIContext* ctx) { return ctx->make<ui::ContainerRenderObject>(); }

void AudioSettings::draw([[maybe_unused]] acos::graphics::Renderer* renderer) {
}

} // namespace acos::apps
