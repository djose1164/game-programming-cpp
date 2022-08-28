#include "components/input_component.h"
#include "actors/actor.h"

#include <SDL2/SDL.h>

InputComponent::InputComponent(Actor *owner)
    : MoveComponent{owner}
    , forward_key_{SDL_SCANCODE_W}
    , back_key_{SDL_SCANCODE_S}
{
}

void InputComponent::process_input(const uint8_t *key_state)
{
    auto forward_speed__{0.f};
    if (key_state[forward_key()])
        forward_speed__ += max_forward_speed();
    if (key_state[back_key()])
        forward_speed__ -= max_forward_speed();    
    forward_speed(forward_speed__);

    auto angular_speed__{0.f};
    if (key_state[clockwise_key()])
        angular_speed__ += max_angular_speed();
    if (key_state[counter_clockwise_key()])
        angular_speed__ -= max_angular_speed();
    angular_speed(angular_speed__);
}

void InputComponent::max_angular_speed(float max_angular_speed)
{
    max_angular_speed_ = max_angular_speed;
}

float InputComponent::max_angular_speed() const
{
    return max_angular_speed_;
}

void InputComponent::max_forward_speed(float max_forward_speed)
{
    max_forward_speed_ = max_forward_speed;
}

float InputComponent::max_forward_speed() const
{
    return max_forward_speed_;
}

void InputComponent::forward_key(int forward_key)
{
    forward_key_ = forward_key;
}

int InputComponent::forward_key() const
{
    return forward_key_;
}

void InputComponent::back_key(int back_key)
{
    back_key_ = back_key;
}

int InputComponent::back_key() const
{
    return back_key_;
}

void InputComponent::clockwise_key(int clockwise_key)
{
    clockwise_key_ = clockwise_key;
}

int InputComponent::clockwise_key() const
{
    return clockwise_key_;
}


void InputComponent::counter_clockwise_key(int counter_clockwise_key)
{
    counter_clockwise_key_ = counter_clockwise_key;
}

int InputComponent::counter_clockwise_key() const
{
    return counter_clockwise_key_;
}

