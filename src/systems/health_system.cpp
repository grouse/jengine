// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: health_system.cpp
// author: Jesper Stefansson

#include "health_system.h"

#include <iostream>

HealthSystem::HealthSystem(Engine* e, GameObjects* o) : 
	System(e, o) {}

HealthSystem::~HealthSystem() {}

void HealthSystem::init() { 
	initialised = true;
}

void HealthSystem::update(float dt) {
	for (auto it = objects->components[ComponentId::HEALTH].begin(); it != objects->components[ComponentId::HEALTH].end(); it++) {
		Health* h = (Health*) (*it);
		
		if (h->health <= 0) 
			objects->trashEntity(h->owner);
		
	}	
}
