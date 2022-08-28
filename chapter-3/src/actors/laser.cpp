#include "actors/laser.h"
#include "actors/asteroid.h"
#include "game.h"
#include "components/sprite_component.h"
#include "components/move_component.h"
#include "components/circle_component.h"

#include <SDL2/SDL.h>

Laser::Laser(Game *game)
    : Actor{game}
    , death_timer_{1.f}
{
    auto sc = new SpriteComponent(this);
    sc->set_texture(game->get_texture("assets/laser.png"));

    auto mv = new MoveComponent(this);
    mv->forward_speed(800.f);
    
    circle_ = new CircleComponent(this);
    circle_->radius(11.f);
}

void Laser::update_actor(float delta_time)
{
    death_timer_ -= delta_time;
    if (death_timer_ < 0)
        state(State::DEAD);
    else
    {
        // Dow we intersect with an asteroid?
        for (auto ast : game()->asteroids())
        {
            SDL_assert(ast);
            SDL_assert(ast->circle());
            if (intersect(*circle_, *ast->circle()))
            {
                // The first asteroid we intersect with,
				// set ourselves and the asteroid to dead
                state(State::DEAD);
                ast->state(State::DEAD);
                break;
            }
        }
    }
}
