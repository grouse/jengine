#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <list>

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/collision.h"
#include "components/shape.h"


namespace JEngine {
	class CollisionSystem : public System {
		public:
			CollisionSystem(GameObjects*);
			virtual ~CollisionSystem();

			virtual void update(float dt);

		private:
			// collision functions
			bool overlaps(glm::vec3, glm::vec3);
			float getOverlap(glm::vec3, glm::vec3);

			bool contains(float, glm::vec3);
			glm::vec3 project(glm::vec3*, glm::vec3);
			glm::vec3 perp(glm::vec3);
	};
}

#endif
