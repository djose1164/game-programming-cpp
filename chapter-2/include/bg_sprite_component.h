#ifndef BG_SPRITE_COMPONENT_H
#define BG_SPRITE_COMPONENT_H

#include "sprite_component.h"
#include "math.h"

#include <SDL2/SDL.h>
#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
    BGSpriteComponent(class Actor *owner, int draw_order=10);

    void update(const float &delta_time) override;

    void draw(SDL_Renderer *renderer) override;

    // Set textures used by the background
    void textures(const std::vector<SDL_Texture *> &textures);

    void screen_size(const Vector2 &size);

    const Vector2 &screen_size() const;

    void scroll_speed(float speed);

    float scroll_speed() const;

private:
    struct BGTexture
    {
        SDL_Texture *texture;
        Vector2 offset;
    };
    // Vector containing every bg texture
    std::vector<BGTexture> bg_textures;

    Vector2 screen_size_;

    float scroll_speed_;
};

#endif //BG_SPRITE_COMPONENT_H
