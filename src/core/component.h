// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: component.h
// author: Jesper Stefansson

#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>

#include "core/entity.h"

#define MAX_COMPONENT (250)

enum EComponentType {
	VELOCITY 		= 0,
	COLLISION		= 1,
    PHYSICS_BODY	= 2,
	MOVEMENT		= 3,
	TEXTURE			= 4,
	DEBUG			= 5,
	MESH			= 6,
	NUM_TYPES
};

struct Component{
	unsigned int id;
	const unsigned int type;

	Component() {}
	Component(unsigned int t) : type(t) {}
	virtual ~Component() {};
};

class ComponentManager {
	Component* components[MAX_COMPONENT][EComponentType::NUM_TYPES] = {0};
	unsigned int next = 0;

	public:
		unsigned int attachComponent(unsigned int, Component*);
};

struct Mesh : public Component {
	// when passing to opengl work out vertices padding by (sizeof(vec3) - sizeof(float)*3)
	unsigned int vertices_size;
	glm::vec3* vertices;

	Mesh(unsigned int size) : Component(EComponentType::MESH) {
		vertices_size = size;
		vertices = new glm::vec3[size];
	};

	virtual ~Mesh() { 
		delete [] vertices;
	}
};

struct PhysicsBody : public Component {
	float friction = 0.0f; 			// =0: constant, >0: factor of velocity lost
	float bounce = 1.0f;			// <1: -accelerate, =1: constant, >1: accelerate
	
	PhysicsBody() : Component(EComponentType::PHYSICS_BODY) {};
};

struct Collision : public Component {
	bool allow_overlap = false; 	// determines whether translation should occur
   	bool allow_translation = true;	// determines whether box should be translated on collision	
	Mesh bounding_box;				// bounding box
	Mesh aa_bounding_box; 			// axis aligned

	Collision(unsigned int size) : 
		bounding_box(size),
		aa_bounding_box(size),
		Component(EComponentType::COLLISION) {};
};

struct Movement : public Component {
	glm::vec3 velocity;
	
	// make into vec3? could have some usage in allowing different max speeds depending on axis
	float max_velocity = 100.0f; 

	Movement() : Component(EComponentType::MOVEMENT) {};
};

struct Texture : public Component {
	unsigned int texture_id;
	unsigned int w, h;

	Texture() : Component(EComponentType::TEXTURE) {};
};

struct Debug : public Component {
	char* key;
	char* value;
	
	Debug() : Component(EComponentType::DEBUG) {};
};


#endif
