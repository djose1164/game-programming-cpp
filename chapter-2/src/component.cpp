#include "component.h"
#include "actor.h"

Component::Component(Actor *owner_, int draw_order)
    : owner{owner_}
    , update_order_{draw_order}
{
    owner->add_component(this);
}

Component::~Component()
{
    owner->remove_component(this);
}

int Component::update_order() const
{
    return update_order_;
}

void Component::update(const float &delta_time)
{

}