#include "ship.h"
#include "game.h"
#include "animated_sprite_component.h"

Ship::Ship(Game *game)
    : Actor{game}
    , right_speed_{0.f}
    , down_speed_{0.f}
{
   auto asc = new AnimatedSpriteComponent(this);
   std::vector<SDL_Texture *> animations{
        game->get_texture("assets/Ship01.png"),
        game->get_texture("assets/Ship02.png"),
        game->get_texture("assets/Ship03.png"),
        game->get_texture("assets/Ship04.png")
   };
    SDL_Log("sprite_texture.size(): %zu", animations.size());
   asc->animated_textures(animations);
}

void Ship::process_keyboard(const u_int8_t *state)
{
    down_speed_ = 0;
    if (state[SDL_SCANCODE_W])
        down_speed_ -= 300.f;
    if (state[SDL_SCANCODE_S])
        down_speed_ += 300.f;
    
    right_speed_ = 0;
    if (state[SDL_SCANCODE_A])
        right_speed_ -= 250.f;
    if(state[SDL_SCANCODE_D])
        right_speed_ += 250.f;
}       

void Ship::update_actor(const float &delta_time)
{
    Actor::update_actor(delta_time);

    Vector2 pos{position()};
    pos.x += right_speed() * delta_time;
    pos.y += down_speed() * delta_time;

    if (pos.x < 25.f)
        pos.x = 25.f;
    else if (pos.x > 500.f)
        pos.x = 500.f;
    
    if (pos.y < 25.f)
        pos.y = 25.f;
    else if (pos.y > 743.f)
        pos.y = 743.f;

    position(pos);
}

float Ship::right_speed() const
{
    return right_speed_;
}

float Ship::down_speed() const
{
    return down_speed_;
}