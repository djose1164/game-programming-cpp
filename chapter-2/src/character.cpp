#include "character.h"
#include "game.h"
#include "animated_sprite_component.h"
#include <string>

Character::Character(Game *game)
    : Actor{game}
{
    auto asc = new AnimatedSpriteComponent(this);
    asc->wrap_mode(AnimatedSpriteComponent::WrapMode::LOOP);
    //Walking - 01 through 06
    std::vector<SDL_Texture *> walking{
        game->get_texture("assets/Character01.png"),
        game->get_texture("assets/Character02.png"),
        game->get_texture("assets/Character03.png"),
        game->get_texture("assets/Character04.png"),
        game->get_texture("assets/Character05.png"),
        game->get_texture("assets/Character06.png")
    };
    // Jumping - 07 through 15
    std::vector<SDL_Texture *> jumping{
        game->get_texture("assets/Character07.png"),
        game->get_texture("assets/Character08.png"),
        game->get_texture("assets/Character09.png"),
        game->get_texture("assets/Character10.png"),
        game->get_texture("assets/Character11.png"),
        game->get_texture("assets/Character12.png"),
        game->get_texture("assets/Character13.png"),
        game->get_texture("assets/Character14.png"),
        game->get_texture("assets/Character15.png")
    };
    // Punch - 16 through 18
    std::vector<SDL_Texture *> punch{
        game->get_texture("assets/Character16.png"),
        game->get_texture("assets/Character17.png"),
        game->get_texture("assets/Character18.png")
    };

    asc->animated_textures(walking);
    asc->animated_textures(jumping);
    asc->animated_textures(punch);
}

float Character::right_speed() const
{
    return right_speed_;
}
    
void Character::right_speed(float right_speed)
{
    right_speed_ = right_speed;
}

void Character::update_actor(const float &delta_time)
{
    Vector2 pos{position()};
    pos.x += right_speed() * delta_time;

    if (pos.x < 50.f)
        pos.x = 50.f;
    else if (pos.x > 1024.f/2.f)
        pos.x = 500.f;

    position(pos);
}

void Character::process_keyboard(const u_int8_t *state)
{
    right_speed(0.f);
    action(Action::WALKING);

    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D])
    {
        action(Action::WALKING);

        if (state[SDL_SCANCODE_A])
            right_speed_ -= 150.f;
        if(state[SDL_SCANCODE_D])
            right_speed_ += 150.f;
    }
    if (state[SDL_SCANCODE_SPACE])
        action(Action::JUMPING);
    if (state[SDL_SCANCODE_J])
        action(Action::PUNCH);
}
