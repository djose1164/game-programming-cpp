#ifndef LASER_H
#define LASER_H

#include "actors/actor.h"

class Laser : public Actor
{
public:
    explicit Laser(class Game *game);

    void update_actor(float delta_time) override;

private:
    class CircleComponent *circle_;
    float death_timer_;
};

#endif //LASER_H
