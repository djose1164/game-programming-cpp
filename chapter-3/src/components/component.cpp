#include "components/component.h"
#include "actors/actor.h"

#include <SDL2/SDL.h>

Component::Component(Actor *owner, int update_order)
    : owner_{owner}
    , update_order_{update_order}
{
    owner_->add_component(this);
}

Component::~Component()
{
    owner_->remove_component(this);
}

void Component::update(float delta_time)
{
}

void Component::process_input(const uint8_t *key_state)
{
}

int Component::update_order() const
{
    return update_order_;
}
