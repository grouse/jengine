// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: entity.cpp
// author: Jesper Stefansson

#include "entity.h"

EntitySystem::~EntitySystem() {
	for (int i = 0; i < MAX_ENTITY; i++)
		delete entities[i];
}

unsigned int EntitySystem::createEntity() {
	entities[next] = new Entity(next);
	return ++next;
}
