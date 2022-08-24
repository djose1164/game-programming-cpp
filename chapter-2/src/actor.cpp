#include "actor.h"
#include "game.h"
#include "component.h"
#include "math.h"

#include <algorithm>

Actor::Actor(Game *game)
    : state_{State::ACTIVE}
    , action_{Action::WALKING}
    , position_(Vector2(0.f, 0.f))
    , scale_{1.f}
    , rotation_{0.f}
    , game_{game}
{
    game->add_actor(this);
}

Actor::~Actor()
{
    game_->remove_actor(this);

    while (!components.empty())
        delete components.back();
}

void Actor::update(const float &delta_time)
{
    if (state() == State::ACTIVE)
    {
        update_components(delta_time);
        update_actor(delta_time);
    }
}

void Actor::update_components(const float &delta_time)
{
    for (auto component: components)
        component->update(delta_time);
}

void Actor::update_actor(const float &delta_time)
{
    // TODO: No idea.
}

void Actor::add_component(Component *component)
{
    auto my_order{component->update_order()};
    auto iter = components.begin();

    // Find higher than me
    for (; iter != components.end(); ++iter)
        if (my_order < (*iter)->update_order())
            break;
    
    components.insert(iter, component);
}

void Actor::remove_component(Component *component)
{
    auto iter = std::find(components.begin(), components.end(), component);
    if (iter != components.end())
        components.erase(iter);
}

Actor::State Actor::state() const
{
    return state_;
}

const Actor::Action &Actor::action() const
{
    return action_;
}

void Actor::action(Action action)
{
    action_ = action;
}

void Actor::scale(float scale)
{
    scale_ = scale;
}

const float &Actor::scale() const
{
    return scale_;
}

const float &Actor::rotation() const
{
    return rotation_;
}

const Vector2 &Actor::position() const
{
    return position_;
}

void Actor::position(const Vector2 &position)
{
    position_ = position;
}

const Game *Actor::game() const
{
    return game_;
}

Game *Actor::game()
{
    return game_;
}
