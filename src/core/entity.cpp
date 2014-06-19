// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: entity.cpp
// author: Jesper Stefansson

#include "entity.h"

Entity::Entity(glm::vec3 vec) : pos(vec) {
	// Set all pointers to 0
	for (unsigned int i = 0; i < ComponentId::NUM_TYPES; i++) 
		components[i] = 0;
}

Entity::Entity(float x, float y, float z) : pos(x, y, z) {
	// Set all pointers to 0
	for (unsigned int i = 0; i < ComponentId::NUM_TYPES; i++) 
		components[i] = 0;
}

Entity::~Entity() {}

int Entity::attach(unsigned int type, Component* c) {
	// Entity already has a component of same type attached
	if (components[type] != 0)
		return -1;
	
	components[type] = c;
	return 0;	
}
