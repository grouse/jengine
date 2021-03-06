// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: collision.cpp
// author: Jesper Stefansson

#include "collision.h"

#include <iostream>

Collision::Collision(void (*response)(Entity*, Entity*, glm::vec3, GameObjects*)) :
	Component(EComponentType::COLLISION) {
	this->response = response;
}

Collision::~Collision() {}

namespace CollisionResponse {
	void rigid_body(Entity* e1, Entity* e2, glm::vec3 overlap, GameObjects* objects) {
		// Move entity so that it no longer overlaps
		// TODO: tunneling occurs in certain scenarios, 
		// investigation and fixing is necessary
		e1->pos += overlap;

		// If the parent entity has a velocity this should be
		// decreased
		// TODO: Implement friction and "bounce-factor" 
		/**if (e1->components[ComponentId::VELOCITY] != 0) {
			Velocity* v = (Velocity*) e1->components[ComponentId::VELOCITY];
			
			v->vec3 *= 0.75;
		}**/
	}

	// Currently, static body just mean the entities are 
	// immovable, which is currently implemented by not doing
	// anything in its collision response
	void static_body(Entity* e1, Entity* e2, glm::vec3 overlap, GameObjects* objects) {
		e2->pos -= overlap;	
	}

	void projectile(Entity* e1, Entity* e2, glm::vec3 overlap, GameObjects* objects) {

		// If the relevant entities contain damage and health 
		// components, health will be deducted from the target
		// based upon the source's damage component
		if (e1->components[EComponentType::DAMAGE] != 0 && e2->components[EComponentType::HEALTH] != 0) {
			Damage* d = (Damage*) e1->components[EComponentType::DAMAGE];
			Health* h = (Health*) e2->components[EComponentType::HEALTH];

			h->health -= d->damage;
			std::cout << "DAMAGE! " << d->damage << "\nRemaining health: " << h->health << "\n";
		}
		
		// Base functionality for projectile response:
		// the projectile has hit a target, so trash it
		objects->trashEntity(e1);
	}
}
