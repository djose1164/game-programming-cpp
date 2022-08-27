#include "actors/actor.h"
#include "game.h"
#include "components/component.h"

#include <algorithm>

Actor::Actor(Game *game__)
    : state_{State::ACTIVE}
    , position_{Vector2::Zero}
    , scale_{1.5f}
    , rotation_{0.f}
    , game_{game__}
{
    game()->add_actor(this);
}

Actor::~Actor()
{
    game()->remove_actor(this);

    while (!components_.empty())
        delete components_.back();
}

void Actor::update(float delta_time)
{
    if (state() == State::ACTIVE)
    {
        update_components(delta_time);
        update_actor(delta_time);
    }
}

void Actor::update_components(float delta_time)
{
    for (auto component : components_)
        component->update(delta_time);
}

void Actor::update_actor(float delta_time)
{
    // To be overriden.
}

void Actor::proccess_input(const uint8_t *key_state)
{ 
    // First proccess input for components
    for (auto component : components_)
        component->process_input(key_state);
    actor_input(key_state);
}

void Actor::actor_input(const uint8_t *key_state)
{
    // To be overriden.
}

void Actor::state(State state)
{
    state_ = state;
}

Actor::State Actor::state() const
{
    return state_;
}

void Actor::position(const Vector2 &position)
{
    position_ = position;
}

const Vector2 &Actor::position() const
{
    return position_;
}

void Actor::scale(float scale)
{
    scale_ = scale;
}

float Actor::scale() const
{
    return scale_;
}

void Actor::rotation(float rotation)
{
    rotation_ = rotation;
}

float Actor::rotation() const
{
    return rotation_;
}

Vector2 Actor::forward() const
{
    return Vector2(
        Math::Cos(rotation()), -Math::Sin(rotation())
    );
}

void Actor::add_component(Component *component)
{
    // Find the correct position for component. Insert it before the higher
    // order than me.
    auto my_order{component->update_order()};
    auto iter{components_.begin()};

    for (; iter != components_.end(); ++iter)
        if (my_order < (*iter)->update_order())
            break;
    
    // Insert before iter.
    components_.insert(iter, component);
}

void Actor::remove_component(Component *component)
{
    auto iter{std::find(components_.begin(), components_.end(), component)};

    if (iter != components_.end())
        components_.erase(iter);
}

Game *Actor::game()
{
    return game_;
}

const Game *Actor::game() const
{
    return game_;
}
