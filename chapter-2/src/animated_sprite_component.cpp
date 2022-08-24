#include "animated_sprite_component.h"
#include "actor.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor *owner, int draw_order)
    : SpriteComponent{owner, draw_order}
    , animation_done_{false}
    , current_frame{0.f}
    , fps_{24.f}
{
}

void AnimatedSpriteComponent::update(const float &delta_time)
{
    // SpriteComponent::update(delta_time);
    auto current_animation = animated_textures_[static_cast<int>(owner->action())];
    if (current_animation.size() < 0)
        return;
    
    current_frame += fps() * delta_time;

    // Wrap current frame if needed
    while (current_frame >= current_animation.size())
        if(wrap_mode() == WrapMode::LOOP)
            current_frame -= current_animation.size();
        else
            return;
    // Set the current texture
    sprite_texture(current_animation[static_cast<int>(current_frame)]);
    animation_done(true);
}

void AnimatedSpriteComponent::animated_textures(const std::vector<SDL_Texture *> &textures)
{
    animated_textures_.push_back(textures);
    if (animated_textures_.size() > 0)
    {
        // Set the active texture to the first frame
        current_frame = 0.f;
        auto current_animation = animated_textures_[static_cast<int>(owner->action())];
        sprite_texture(current_animation[0]);
    }
}

const float &AnimatedSpriteComponent::fps() const
{
    return fps_;
}

void AnimatedSpriteComponent::wrap_mode(WrapMode wrap_mode)
{
    wrap_mode_ = wrap_mode;
}

AnimatedSpriteComponent::WrapMode AnimatedSpriteComponent::wrap_mode() const
{
    return wrap_mode_;
}
