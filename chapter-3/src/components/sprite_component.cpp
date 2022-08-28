#include "components/sprite_component.h"
#include "actors/actor.h"
#include "game.h"

SpriteComponent::SpriteComponent(Actor *owner, int draw_order)
    : Component{owner}
    , texture_{nullptr}
    , draw_order_{draw_order}
    , texture_width_{0}
    , texture_height_{0}
{
    owner_->game()->add_sprite(this);
}

SpriteComponent::~SpriteComponent()
{
    owner_->game()->remove_sprite(this);
}

void SpriteComponent::draw(SDL_Renderer *renderer)
{
    if (!texture_)
        return;

    SDL_Rect r;

    // Scale width and height by owner's scale.
    r.w = static_cast<int>(texture_width() * owner_->scale());
    r.h = static_cast<int>(texture_height() * owner_->scale());
    // Center rectangle around owner.
    r.x = static_cast<int>(owner_->position().x - r.w/2);
    r.y = static_cast<int>(owner_->position().y - r.h/2);

    SDL_RenderCopyEx(
        renderer,
        texture_,
        nullptr,
        &r,
        -Math::ToDegrees(owner_->rotation()),
        nullptr,
        SDL_FLIP_NONE
    );
}

void SpriteComponent::set_texture(SDL_Texture *texture)
{
    texture_ = texture;

    SDL_QueryTexture(
        texture,
        nullptr,
        nullptr,
        &texture_width_,
        &texture_height_
    );
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
