#ifndef CIRCLE_COMPONENT_H
#define CIRCLE_COMPONENT_H

#include "components/component.h"
#include "utils/Math.h"
class CircleComponent : public Component
{
public:
    CircleComponent(Actor *owner);

    const Vector2 &center() const;

    void radius(float radius);
    float radius() const;

private:
    float radius_;
};

bool intersect(const CircleComponent &a, const CircleComponent &b);

#endif // CIRCLE_COMPONENT_H
