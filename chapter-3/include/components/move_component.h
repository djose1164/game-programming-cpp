#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include "components/component.h"

class MoveComponent : public Component
{
public:
    // Lower update order to update first.
    MoveComponent(class Actor *owner, int update_order  = 10);

    void update(float delta_time) override;

    void angular_speed(float angular_speed);
    float angular_speed() const;

    void forward_speed(float forward_speed);
    float forward_speed() const;

private:
    float angular_speed_;
    float forward_speed_;
};

#endif //MOVE_COMPONENT_H
