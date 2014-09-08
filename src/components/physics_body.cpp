#include "physics_body.h"

PhysicsBody::PhysicsBody(bool gravity) : Component(ComponentId::PHYSICS_BODY) {
    this->gravity = gravity;
}

PhysicsBody::~PhysicsBody() {}
