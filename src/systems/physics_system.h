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

#include "ecs/components.hpp"
#include "ecs/component_manager.h"
#include "ecs/entity_manager.h"

class PhysicsSystem {
    glm::vec3 gravity;

public:
	void init(glm::vec3);
	virtual void update(float dt);

	//void addRotation(Entity*, float);
};

#endif
