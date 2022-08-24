#ifndef CHARACTER_H
#define CHARACTER_H

#include "actor.h"

class Character : public Actor
{
public:

    Character(class Game *game);

    void update_actor(const float &delta_time) override;

    void process_keyboard(const u_int8_t *state);
    
    float right_speed() const;
    
    void right_speed(float right_speed);

private:
    float right_speed_;
};

#endif // CHARACTER_H
