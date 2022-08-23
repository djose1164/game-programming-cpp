#ifndef SHIP_H
#define SHIP_H

#include "actor.h"

class Ship : public Actor
{
public:
    Ship(class Game *game);

    void update_actor(const float &delta_time) override;

    void process_keyboard(const u_int8_t *state);

    float right_speed() const;

    float down_speed() const;

private:
    float right_speed_;
    float down_speed_;
};

#endif //SHIP_H
