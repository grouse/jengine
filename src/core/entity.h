// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: entity.h
// author: Jesper Stefansson
//
// Contains the Entity class, which is not much more than a position
// and a list of its attached components. 
#ifndef ENTITY_H
#define ENTITY_H

#include <glm/vec3.hpp>

#include "core/component.h"

// See file comments for class details 
class Entity {
	public:

		// Initialise the entity with parameters as position,
		// also iterates through the list of components and sets
		// the pointers to 0
		Entity(float, float, float);	// x, y, z
		Entity(glm::vec3);				// glm::vec3(x, y, z)

		~Entity();

		glm::vec3 pos;	// Position of entity in world space

		// Attaches the Component to the entity if the Entity
		// does not already contain a component of that type
		// 
		// Returns:
		// 		-1: component already exists
		// 		 0: component successfully attached
		int attach(unsigned int, Component*);

		// Array of component pointers, which are 0 if no
		// component of a specified type is attached.
		Component* components[EComponentType::NUM_TYPES];
};

#endif
