#ifndef SHIP_H
#define SHIP_H

#include "actors/actor.h"

class Ship : public Actor
{
public:
    explicit Ship(class Game *game);

    void update_actor(float delta_time) override;

    void actor_input(const uint8_t *key_state) override;

private:
    float laser_cooldown_;
};

#endif //SHIP_H