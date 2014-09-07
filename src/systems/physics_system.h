// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: movement_system.h
// author: Jesper Stefansson
//
// Contains the PhysicsSystem, which manages velocity and thrust
// updates

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/velocity.h"
#include "components/shape.h"

class PhysicsSystem : public System {
public:
    PhysicsSystem(Engine*, GameObjects*, glm::vec3);
	virtual ~PhysicsSystem();

	virtual void init();

	virtual void update(float dt);

	void addRotation(Entity*, float);
private:
    glm::vec3 gravity;
};

#endif
