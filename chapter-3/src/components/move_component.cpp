#include "components/move_component.h"
#include "actors/actor.h"
#include "utils/Math.h"

MoveComponent::MoveComponent(Actor *owner, int update_order)
    : Component{owner, update_order}
    , angular_speed_{0.f}
    , forward_speed_{0.f}
{
}

void MoveComponent::update(float delta_time)
{
    if (!Math::NearZero(angular_speed()))
    {
        auto rotation{owner_->rotation()};
        rotation += angular_speed() * delta_time;
        owner_->rotation(rotation);
    }

    if (!Math::NearZero(forward_speed()))
    {
        auto position{owner_->position()};
        position += owner_->forward() * forward_speed() * delta_time;

        // Screen wrapping code only for asteroids.
        if (position.x < 0.f)
            position.x = 1022.f;
        else if (position.x > 1024.f)
            position.x = 2.f;
        if (position.y < 0.f)
            position.y = 766.f;
        else if (position.y > 768.f)
            position.y = 2.f;
        owner_->position(position);
    }
}

void MoveComponent::angular_speed(float angular_speed)
{
    angular_speed_ = angular_speed;
}

float MoveComponent::angular_speed() const
{
    return angular_speed_;
}

void MoveComponent::forward_speed(float forward_speed)
{
    forward_speed_ = forward_speed;
}

float MoveComponent::forward_speed() const
{
    return forward_speed_;
}
