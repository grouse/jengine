#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

#include "core/entity.h"
#include "core/component.h"

class PhysicsBody : public Component{
public:
    PhysicsBody(bool);
    virtual ~PhysicsBody();
    bool canAttach(Entity&);

    bool gravity;
};

#endif
