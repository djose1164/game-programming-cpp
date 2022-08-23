#include "sprite_component.h"
#include "actor.h"
#include "game.h"

SpriteComponent::SpriteComponent(Actor *actor, int draw_order)
    : Component{actor, draw_order}
    , sprite_texture_{nullptr}
    , draw_order_{draw_order}
    , texture_width_{0}
    , texture_height_{0}
{
    owner->game()->add_sprite(this);
}

SpriteComponent::~SpriteComponent()
{
    owner->game()->remove_sprite(this);
}

int SpriteComponent::draw_order() const
{
    return draw_order_;
}

int SpriteComponent::texture_width() const
{
    return texture_width_;
}

int SpriteComponent::texture_height() const
{
    return texture_height_;
}

void SpriteComponent::sprite_texture(SDL_Texture *texture)
{
    sprite_texture_ = texture;
    // Get width & height of texture.
    SDL_QueryTexture(
        sprite_texture_,
        nullptr,
        nullptr,
        &texture_width_,
        &texture_height_
    );
}

void SpriteComponent::draw(SDL_Renderer *renderer)
{
    if (!sprite_texture_)
        return;

    SDL_Rect r;

    // Scale the width/height by owner's scale.
    r.w = static_cast<int>(texture_width() * owner->scale());
    r.h = static_cast<int>(texture_height() * owner->scale());

    // Center the rect about the position of the owner
    r.x = static_cast<int>(owner->position().x - r.w / 2);
    r.y = static_cast<int>(owner->position().y - r.h / 2);

    // Draw
    SDL_RenderCopyEx(
        renderer,
        sprite_texture_,
        nullptr,
        &r,
        -Math::ToDegrees(owner->rotation()),
        nullptr,
        SDL_FLIP_NONE
    );
    
}