/**
 * @file component.h
 * @author Daniel Victoriano (@djose1164)
 * @brief Component abstract class.
 * @version 0.1
 * @date 2022-08-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

class Actor; /* Forward declaration. */

/**
 * @brief Abstract class to create specialized components. Each component has to
 * be owned by an `Actor` object. See `actor.h`.
 * 
 */
class Component
{
public:
    /**
     * @brief Construct a new Component object.
     * 
     * @param owner Owner of this component.
     * @param update_order The lowest, the earlier this component updates
     */
    Component(Actor *owner, int update_order = 100);

    /**
     * @brief Destroy the Component object
     * 
     */
    virtual ~Component();

    /**
     * @brief Update component.
     * 
     * @param delta_time Update component by.
     */
    virtual void update(float delta_time);

    virtual void process_input(const uint8_t *key_state);

    int update_order() const;

protected:
    Actor *owner_; /* Current owner of this component. */

    int update_order_; /* Priority order to update; see ctr.*/
};

#endif //COMPONENT_H
