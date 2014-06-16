// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: collision_system.h
// author: Jesper Stefansson
//
// Contains the CollisionSystem, which handles the collision 
// detection and triggering the attached collision response

#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <list>

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/engine.h"
#include "core/game_objects.h"

#include "components/collision.h"
#include "components/shape.h"


namespace JEngine {
	namespace Systems {

		// See file comments for class details
		class CollisionSystem : public Core::System {
			public:
				CollisionSystem(Core::Engine*, Core::GameObjects*);
				virtual ~CollisionSystem();

				virtual void init();
				virtual void update(float dt);

			private:
				// Returns true if the two vectors overlap, uses
				// CollisionSystem::contains to determine overlap 
				bool overlaps(glm::vec3, glm::vec3);
				
				// Returns true if the float is inside the vector
				bool contains(float, glm::vec3);

				// Returns the overlap scalar between the two vectors
				float getOverlap(glm::vec3, glm::vec3);

				// Projects the first parameter onto the second parameter
				// vector.
				glm::vec3 project(glm::vec3*, glm::vec3);

				// Calculates the perpendicular vector of the parameter
				glm::vec3 perp(glm::vec3);
		};
	}
}

#endif
