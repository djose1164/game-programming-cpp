/**
 * @file actor.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-08-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ACTOR_H
#define ACTOR_H

#include "utils/Math.h" /* For Vector2. */

#include <cstdint> /* For uint8_t. */
#include <vector>

class Game;      /* Forward declaration. */
class Component; /* Forward declaration. */

class Actor
{
public:
    enum class State
    {
        ACTIVE,
        PAUSED,
        DEAD
    };

    /**
     * @brief Construct a new Actor object.
     *
     * @param game Game where this actor resides in.
     */
    Actor(Game *game);

    /**
     * @brief Destroy the Actor object.
     *
     */
    virtual ~Actor();

    /**
     * @brief Update method called from game (not overridable).
     *
     * @param delta_time Time to be updated by.
     */
    void update(float delta_time);

    /**
     * @brief Update components attached to this actor (not overridable).
     *
     * @param delta_time Time to be updated by.Time to be updated by
     */
    void update_components(float delta_time);

    /**
     * @brief Any actor specific update code (overridable).
     *
     * @param delta_time
     */
    virtual void update_actor(float delta_time);

    /**
     * @brief Method called from game (not overridable).
     *
     * @param key_state Array of key states.
     */
    void proccess_input(const uint8_t *key_state);

    /**
     * @brief Any actor specific input code (overridable).
     *
     * @param key_state Array of key states.
     */
    void actor_input(const uint8_t *key_state);

    /**
     * @brief Set actor's state.
     *
     * @param state New state to set.
     */
    void state(State state);

    /**
     * @brief Get actor's state.
     *
     * @return State Current state.
     */
    State state() const;

    /**
     * @brief Set actor's position.
     *
     * @param position New position.
     */
    void position(const Vector2 &position);

    /**
     * @brief Get actor's state.
     *
     * @return const Vector2& Current position.
     */
    const Vector2 &position() const;

    /**
     * @brief Set actor's scale.
     *
     * @param scale New scale.
     */
    void scale(float scale);

    /**
     * @brief Get actor's scale.
     *
     * @return float Current scale.
     */
    float scale() const;

    /**
     * @brief Set actor's rotation.
     *
     * @param rotation New rotation.
     */
    void rotation(float rotation);

    /**
     * @brief Get actor's rotation.
     *
     * @return float Current rotation.
     */
    float rotation() const;

    /**
     * @brief Get forward speed.
     *
     * @return const Vector2& Forward speed.
     */
    Vector2 forward() const;

    /**
     * @brief Attach a new component to this actor.
     *
     * @param component Component to attach.
     */
    void add_component(Component *component);

    /**
     * @brief Remove an existing component from this actor. THe memory used by
     * `component` is released.
     *
     * @param component Component to delete. Is safe passing null.
     */
    void remove_component(Component *component);

    /**
     * @brief Set actor's game.
     *
     * @param game New game pointer.
     */
    void game(const Game *game);

    /**
     * @brief Get actor's const pointer to game (const).
     *
     * @return const Game* Const game pointer.
     */
    const Game *game() const;

    /**
     * @brief Get actor's pointer to game (mutable).
     *
     * @return Game* Game pointer.
     */
    Game *game();

private:
    State state_;

    Vector2 position_;

    float scale_;
    float rotation_;

    std::vector<Component *> components_;

    Game *game_;
};

#endif // ACTOR_H
