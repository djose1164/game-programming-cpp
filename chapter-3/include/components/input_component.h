#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "components/move_component.h"

class InputComponent : public MoveComponent
{
public:
    explicit InputComponent(class Actor *owner);

    void process_input(const uint8_t *key_state) override;

    void max_angular_speed(float max_angular_speed);
    float max_angular_speed() const;

    void max_forward_speed(float max_forward_speed);
    float max_forward_speed() const;

    void forward_key(int forward_key);
    int forward_key() const;

    void back_key(int back_key);
    int back_key() const;

    void clockwise_key(int clockwise_key);
    int clockwise_key() const;

    void counter_clockwise_key(int counter_clockwise_key);
    int counter_clockwise_key() const;

private:
    float max_angular_speed_;
    float max_forward_speed_;

    int forward_key_;
    int back_key_;

    // Keys for angular movement
    int clockwise_key_;
    int counter_clockwise_key_;
};

#endif //INPUT_COMPONENT_H
