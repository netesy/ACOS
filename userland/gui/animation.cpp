#include "animation.h"
#include "context.h"

namespace acos::ui {

void AnimationManager::update(UIContext* ctx, u64 now) {
    auto node = m_animations.head();
    while (node) {
        node->value->tick(ctx, now);
        node = node->next;
    }
}

void AnimationManager::add_animation(UIContext* ctx, Animation* anim) {
    m_animations.add(ctx->region(), anim);
}

} // namespace acos::ui
