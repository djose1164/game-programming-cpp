#include "animated_sprite_component.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor *owner, int draw_order)
    : SpriteComponent{owner, draw_order}, current_frame{0.f}, fps_{24.f}
{
}

void AnimatedSpriteComponent::update(const float &delta_time)
{
    // SpriteComponent::update(delta_time);

    if (animated_textures_.size() > 0)
        current_frame += fps() * delta_time;

    // Wrap current frame if needed
    if (current_frame > animated_textures_.size())
        current_frame -= animated_textures_.size();
    // Set the current texture
    sprite_texture(animated_textures_[static_cast<int>(current_frame)]);
}

void AnimatedSpriteComponent::animated_textures(const std::vector<SDL_Texture *> &textures)
{
    animated_textures_ = textures;
    if (animated_textures_.size() > 0)
    {
        // Set the active texture to the first frame
        current_frame = 0.f;
        sprite_texture(animated_textures_[0]);
    }
}

const float &AnimatedSpriteComponent::fps() const
{
    return fps_;
}
