// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: movement_system.cpp
// author: Jesper Stefansson

#include "movement_system.h"

MovementSystem::MovementSystem(Engine* e, GameObjects* o) :
   System(e, o) {}

MovementSystem::~MovementSystem() {}

void MovementSystem::init() {
	initialised = true;
}

void MovementSystem::update(float dt) {
	for (auto it = objects->components[ComponentId::VELOCITY].begin(); it != objects->components[ComponentId::VELOCITY].end(); it++) {

		Velocity* v = (Velocity*) (*it);
		Entity* e = v->owner;;

		e->pos += v->vec3 * dt;
	}
}
