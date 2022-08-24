#ifndef ACTOR_H
#define ACTOR_H

#include "math.h"
#include <vector>

class Actor
{
public:
    enum class State
    {
        ACTIVE,
        PAUSED,
        DEAD
    };

    enum class Action
    {
        WALKING,
        JUMPING,
        PUNCH
    };

    Actor(class Game *game);

    virtual ~Actor();

    State state() const;

    const Action &action() const;

    void action(Action action);

    // Update function called from game (not overridable)
    void update(const float &delta_time);

    // Update all the components attached to actor (not overridable)
    void update_components(const float &delta_time);

    // Any actor-specific update code (overridable)
    virtual void update_actor(const float &delta_time);

    void add_component(class Component *component);

    void remove_component(class Component *component);

    void scale(float scale);

    const float &scale() const;

    const float &rotation() const;

    const Vector2 &position() const;

    void position(const Vector2 &position);

    const class Game *game() const;

    class Game *game();

private:
    State state_;
    Action action_;

    Vector2 position_; // Center position of actor.

    float scale_;
    float rotation_;

    class Game *game_;

    // Components held by this actor
    std::vector<class Component *> components;
};

#endif // ACTOR_H
