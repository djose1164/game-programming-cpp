#ifndef ASTEROID_H
#define ASTEROID_H

#include "actors/actor.h"

class Asteroid : public Actor
{
public:
    Asteroid(class Game *game);
    ~Asteroid();

    class CircleComponent *circle();
    const class CircleComponent *circle() const;

private:
    class CircleComponent *circle_;
};

#endif //ASTEROID_H
