#include "actors/ship.h"
#include "actors/laser.h"
#include "game.h"
#include "components/sprite_component.h"
#include "components/input_component.h"

Ship::Ship(Game *game)
    : Actor{game}
    , laser_cooldown_{0.f}
{
    auto sc = new SpriteComponent(this, 150);
    sc->set_texture(game->get_texture("assets/ship.png"));

    auto ic = new InputComponent(this);
    ic->forward_key(SDL_SCANCODE_W);
    ic->back_key(SDL_SCANCODE_S);
    ic->clockwise_key(SDL_SCANCODE_A);
    ic->counter_clockwise_key(SDL_SCANCODE_D);
    ic->max_forward_speed(300.f);
    ic->max_angular_speed(Math::TwoPi);
}

void Ship::update_actor(float delta_time)
{
    laser_cooldown_ -= delta_time;
}

void Ship::actor_input(const uint8_t *key_state)
{
    if (key_state[SDL_SCANCODE_SPACE] && laser_cooldown_ <= 0.f)
    {
        // Create a laser a set its position and rotation to mine.
        auto laser{new Laser(game())};
        laser->position(position());
        laser->rotation(rotation());

        // Reset.
        laser_cooldown_ = .5f;
    }
}