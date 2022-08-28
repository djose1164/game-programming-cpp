#include "components/circle_component.h"
#include "actors/actor.h"

CircleComponent::CircleComponent(Actor *owner)
    : Component{owner}
    , radius_{0.f}
{
}

const Vector2 &CircleComponent::center() const
{
    return owner_->position();
}

void CircleComponent::radius(float radius)
{
    radius_ = radius;
}

float CircleComponent::radius() const
{
    return radius_;
}

bool intersect(const CircleComponent &a, const CircleComponent &b)
{
    // Calculate distance squared.
    auto diff{a.center() - b.center()};
    auto dist_squared{diff.LengthSq()};

    // Calculate sum of radii squared.
    auto radii_squared{a.radius() + b.radius()};
    radii_squared *= radii_squared;

    return dist_squared <= radii_squared;
}
