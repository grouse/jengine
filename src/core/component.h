// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: component.h
// author: Jesper Stefansson

#ifndef COMPONENT_H
#define COMPONENT_H

#include "core/entity.h"

#define MAX_COMPONENT (250)

enum EComponentType {
	VELOCITY 		= 0,
	COLLISION		= 1,
    PHYSICS_BODY	= 2,
	MOVEMENT		= 3,
	TEXTURE			= 4,
	DEBUG			= 5,
	NUM_TYPES
};

struct Component{
	unsigned int id;
	const unsigned int type;

	Component() {}
	Component(unsigned int t) : type(t) {}
};

class ComponentManager {
	Component* components[EComponentType::NUM_TYPES][MAX_COMPONENT] = {0};
	unsigned int next = 0;

	public:
		unsigned int attachComponent(unsigned int, Component*);

};

struct PhysicsBody : public Component {
	float friction = 0.0f; 
	float bounce = 1.0f;
	
	PhysicsBody() : Component(EComponentType::PHYSICS_BODY) {};
};

struct Collision : public Component {
	bool allowOverlap = false; 
	bool rotatable = false;
	// Mesh BoundingBox;
	// Mesh AxisAlignedBoundingBox; // implement in some other way?
	
	Collision() : Component(EComponentType::COLLISION) {};
};

struct Movement : public Component {
	// Vector3 velocity;
	
	// make into vector3? could have some usage in allowing different max speeds depending on axis
	float max_velocity = 100.0f; 

	Movement() : Component(EComponentType::MOVEMENT) {};
};

struct Texture : public Component {
	unsigned int texture_id;
	Texture() : Component(EComponentType::TEXTURE) {};
};

struct Debug : public Component {
	char* key;
	char* value;
	
	Debug() : Component(EComponentType::DEBUG) {};
};


#endif
