// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: life_time_system.cpp
// author: Jesper Stefansson

#include "life_time_system.h"

LifeTimeSystem::LifeTimeSystem(Engine* e, GameObjects* o) : 
	System(e, o) {}

LifeTimeSystem::~LifeTimeSystem() {}

void LifeTimeSystem::init() {
	initialised = true;
}

void LifeTimeSystem::update(float dt) {
	for (auto it = objects->components[ComponentId::LIFETIME].begin(); it != objects->components[ComponentId::LIFETIME].end(); it++) {
		LifeTime* c = (LifeTime*) (*it);

		c->remaining -= dt;
		if (c->remaining <= 0)
			objects->trashEntity(c->owner);
	}
	
}
