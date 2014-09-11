#include "physics_body.h"

PhysicsBody::PhysicsBody(bool gravity) : 
	Component(EComponentType::PHYSICS_BODY) {
    this->gravity = gravity;
}

PhysicsBody::~PhysicsBody() {}
