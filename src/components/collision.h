// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: collision.h
// author: Jesper Stefansson
//
// File contains the collision component and the available
// collision responses. 

#ifndef COLLISION_H
#define COLLISION_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"

#include "components/damage.h"
#include "components/health.h"
#include "components/velocity.h"

namespace JEngine {
	namespace Components {

		// The collision component is used to flag the entity
		// for collision detection to the CollisionSystem, the 
		// collision response is defined by a function pointer 
		// passed as paramter to the Collision component
		class Collision : public Core::Component {
			public:
				Collision(void (*response)(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*));
				virtual ~Collision();

				// Returns true if Entity has an attach Shape
				// component
				virtual bool canAttach(Core::Entity&);

				// The attached collision response, called by
				// CollisionSystem if a collision is detected
				//
				// Parameters are: this, other, overlap, objects
				void (*response)(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*);
		};
	}

	namespace CollisionResponse {
		// The rigid body response will move the entity until they
		// no longer overlap, based on overlap parameter. 
		// 
		// If the entity has a Velocity it will reduce the velocity
		// vector
		void rigid_body(Core::Entity*, Core::Entity*, glm::vec3,  Core::GameObjects*);

		// Static bodies exist in the world as immovable objects, as
		// such a static collision response does nothing to either
		// objects
		void static_body(Core::Entity*, Core::Entity*, glm::vec3,  Core::GameObjects*);

		// The projectile response checks whether the appropriate damage
		// and health components exists and deducts health based on these,
		// it will also push the parent entity onto the object trash for
		// deletion.
		void projectile(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*);
	}
}

#endif
