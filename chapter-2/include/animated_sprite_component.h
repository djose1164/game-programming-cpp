#ifndef ANIMATED_SPRITE_COMPONENT_H
#define ANIMATED_SPRITE_COMPONENT_H

#include "sprite_component.h"

#include <vector>

class AnimatedSpriteComponent : public SpriteComponent
{
public:
    enum class WrapMode
    {
        ONCE,
        LOOP
    };

    AnimatedSpriteComponent(class Actor *owner, int draw_order = 100);

    // Update animation every frame (overriden from Component)
    void update(const float &delta_time) override;

    // Set textures used for animation
    void animated_textures(const std::vector<SDL_Texture *> &textures);

    const float &fps() const;

    /**
     * @brief Set wrap mode to use.
     *
     * @param wrap_mode Once or loop.
     */
    void wrap_mode(WrapMode wrap_mode);

    /**
     * @brief Get wrap mode set.
     *
     * @return WrapMode The current wrope mode.
     */
    WrapMode wrap_mode() const;

    bool animation_done() const { return animation_done_; }
    void animation_done(bool animation_done) { animation_done_ = animation_done; }

private:
    // All textures in animation
    std::vector<std::vector<SDL_Texture *>> animated_textures_;

    bool animation_done_;

    WrapMode wrap_mode_;
    // Current frame displayed
    float current_frame;
    // Animation frame rate
    float fps_;
};

#endif // ANIMATED_SPRITE_COMPONENT_H
