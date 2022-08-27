#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "components/component.h"

#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor *owner, int draw_order = 100);
    ~SpriteComponent();

    virtual void draw(SDL_Renderer *renderer);
    virtual void set_texture(SDL_Texture *texture);

    int draw_order() const;
    int texture_width() const;
    int texture_height() const;

private:
    SDL_Texture *texture_;

    int draw_order_;
    int texture_width_;
    int texture_height_;
};

#endif //SPRITE_COMPONENT_H
