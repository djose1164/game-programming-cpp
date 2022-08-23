#ifndef ANIMATED_SPRITE_COMPONENT_H
#define ANIMATED_SPRITE_COMPONENT_H

#include "sprite_component.h"

#include <vector>

class AnimatedSpriteComponent : public SpriteComponent
{
public:
    AnimatedSpriteComponent(class Actor *owner, int draw_order = 100);

    // Update animation every frame (overriden from Component)
    void update(const float &delta_time) override;

    // Set textures used for animation
    void animated_textures(const std::vector<SDL_Texture *> &textures);

    const float &fps() const;

private:
    // All textures in animation
    std::vector<SDL_Texture *> animated_textures_;

    // Current frame displayed
    float current_frame;
    // Animation frame rate
    float fps_;
};

#endif // ANIMATED_SPRITE_COMPONENT_H
