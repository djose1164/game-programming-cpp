#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component(class Actor *owner, int update_order = 100);

    virtual ~Component();

    virtual void update(const float &delta_time);

    int update_order() const;

protected:
    class Actor *owner;
    int update_order_;
};

#endif // COMPONENT_H
