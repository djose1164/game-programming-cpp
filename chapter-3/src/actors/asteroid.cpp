#include "actors/asteroid.h"
#include "utils/random.h"
#include "game.h"
#include "components/sprite_component.h"
#include "components/move_component.h"

Asteroid::Asteroid(Game *game_)
    : Actor{game_}
    , circle_{nullptr}
{
    // Init to random
    auto pos = Random::get_vector(
        Vector2::Zero, Vector2(
            game()->screen_width(), game()->screen_height()
        )
    );

    position(pos);
    rotation(Random::get_float_range(0.f, Math::TwoPi));

    auto sc = new SpriteComponent(this);
    sc->set_texture(game()->get_texture("assets/asteroid.png"));

    auto mv = new MoveComponent(this);
    mv->forward_speed(150.f);

    game()->add_asteroid(this);
}

Asteroid::~Asteroid()
{
    game()->remove_asteroid(this);
}
