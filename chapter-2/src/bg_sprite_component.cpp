#include "bg_sprite_component.h"
#include "actor.h"

BGSpriteComponent::BGSpriteComponent(Actor *owner_, int draw_order)
    : SpriteComponent{owner_, draw_order}
    , scroll_speed_{0.f}
{}

void BGSpriteComponent::textures(const std::vector<SDL_Texture *> &textures)
{
    int count{};
    for (auto texture: textures)
    {
        BGTexture tmp;
        tmp.texture = texture;
        // Each texture is screen width in offset
        tmp.offset.x = count * screen_size().x;
        tmp.offset.y = 0;
        bg_textures.emplace_back(tmp);
        ++count;
    }
}

void BGSpriteComponent::update(const float &delta_time)
{
    SpriteComponent::update(delta_time);

    for (auto &bg: bg_textures)
    {
        bg.offset.x += delta_time * scroll_speed();
        // If this's completely off the screen, reset offset to the right of
        // last background texture
        if (bg.offset.x <= -screen_size().x)
            bg.offset.x = (bg_textures.size() - 1)*screen_size().x - 1;
        
    }
}

void BGSpriteComponent::draw(SDL_Renderer *renderer)
{
    // Draw each background texture
    for (auto &bg: bg_textures)
    {
        SDL_Rect r;
        r.w = screen_size().x,
        r.h = screen_size().y,
        // Center the rectangle around the position of the owner
        r.x = static_cast<int>(owner->position().x - r.w/2 - bg.offset.x);
        r.y = static_cast<int>(owner->position().y - r.h/2 - bg.offset.y);

        SDL_RenderCopy(
            renderer,
            bg.texture,
            nullptr,
            &r
        );
    }
}

void BGSpriteComponent::scroll_speed(float speed)
{
    scroll_speed_ = speed;
}

float BGSpriteComponent::scroll_speed() const
{
    return scroll_speed_;
}

void BGSpriteComponent::screen_size(const Vector2 &size)
{
    screen_size_ = const_cast<Vector2 &>(size);
}

const Vector2 &BGSpriteComponent::screen_size() const
{
    return screen_size_;
}