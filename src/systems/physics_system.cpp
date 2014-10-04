// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: physics_system.cpp
// author: Jesper Stefansson

#include <iostream>

#include "physics_system.h"


void PhysicsSystem::init(glm::vec3 gravity) {
	this->gravity = gravity;
}

void PhysicsSystem::update(float dt) {

	for (unsigned int i = 0; i < components.movement.next; i++) {
		unsigned int entity = components.movement.cmp_ent_id[i];
		
		Movement* movement = components.movement.getCmpFrom(entity);
		Position* position = components.position.getCmpFrom(entity);

		position->x += movement->velocity.x*dt;
		position->y += movement->velocity.y*dt;
		position->z += movement->velocity.z*dt;
	}

	for (unsigned int i = 0; i < components.physics_body.next; i++) {
		PhysicsBody* physics = &components.physics_body[i];
		if (physics->gravity) {
			unsigned int entity = components.physics_body.cmp_ent_id[i];
			Movement* movement = components.movement.getCmpFrom(entity);

			movement->velocity += gravity*dt;
		}

	}
		
	/**for (auto it = objects->components[EComponentType::SHAPE].begin(); it != objects->components[EComponentType::SHAPE].end(); it++) {
		Shape* s = (Shape*)(*it);
		s->rotate(s->rotationRate*dt);
	}

	// (De)accelerate entities and update positions
    for (auto it = objects->components[EComponentType::VELOCITY].begin(); it != objects->components[EComponentType::VELOCITY].end(); it++) {

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
        if(v->owner->components[EComponentType::PHYSICS_BODY]){
            new_velocity +=gravity*dt;
        }


		v->vec3 = new_velocity;

		e->pos += v->vec3 * dt;
	}**/


}

/**void PhysicsSystem::addRotation(Entity* e, float rate) {
	if (e->components[EComponentType::SHAPE] == 0)
		return;
	
	Shape* s = (Shape*) e->components[EComponentType::SHAPE];
	s->rotationRate = rate;
}**/
