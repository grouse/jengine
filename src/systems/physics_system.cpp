// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: physics_system.cpp
// author: Jesper Stefansson

#include <iostream>

#include "physics_system.h"

PhysicsSystem::PhysicsSystem(Engine* e, GameObjects* o,glm::vec3 g) :
   System(e, o) {
    this->gravity = g;
}

PhysicsSystem::~PhysicsSystem() {}

void PhysicsSystem::init() {
	initialised = true;
}

void PhysicsSystem::update(float dt) {
		
	for (auto it = objects->components[ComponentId::SHAPE].begin(); it != objects->components[ComponentId::SHAPE].end(); it++) {
		Shape* s = (Shape*)(*it);
		s->rotate(s->rotationRate*dt);
	}

	// (De)accelerate entities and update positions
    for (auto it = objects->components[ComponentId::VELOCITY].begin(); it != objects->components[ComponentId::VELOCITY].end(); it++) {

		Velocity* v = (Velocity*) (*it);
		Entity* e = v->owner;

		glm::vec3 new_velocity = v->vec3;

		if (v->accelerateForward != 0.0f || v->accelerateSide != 0.0f) {
			glm::vec3 thrust = glm::normalize(glm::vec3(v->accelerateSide, v->accelerateForward, 0.0f));
			thrust *= dt*v->acceleration;

			if (glm::length(v->vec3 + thrust) <= v->max_speed)
				new_velocity = v->vec3 + thrust;
		} else {
			glm::vec3 deaccel = glm::normalize(v->vec3)*dt*v->deacceleration;
			
			if (glm::length(v->vec3 - deaccel) < glm::length(v->vec3))
				new_velocity = v->vec3 - deaccel;
		}
        if(v->owner->components[ComponentId::PHYSICS_BODY]){
            new_velocity +=gravity*dt;
        }


		v->vec3 = new_velocity;

		e->pos += v->vec3 * dt;
	}


}

void PhysicsSystem::addRotation(Entity* e, float rate) {
	if (e->components[ComponentId::SHAPE] == 0)
		return;
	
	Shape* s = (Shape*) e->components[ComponentId::SHAPE];
	s->rotationRate = rate;
}
