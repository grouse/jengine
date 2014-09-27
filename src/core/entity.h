// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: entity.h
// author: Jesper Stefansson
//
// Contains the Entity class, which is not much more than a position
// and a list of its attached components. 
#ifndef ENTITY_H
#define ENTITY_H

#define MAX_ENTITY (250)

struct Entity {
	unsigned int id;
	Entity(unsigned int i) : id(i) {}
};

class EntitySystem {
	Entity* entities[MAX_ENTITY];
	unsigned int next = 0;

	public:
		~EntitySystem();
	 	unsigned int createEntity();
};

#endif
