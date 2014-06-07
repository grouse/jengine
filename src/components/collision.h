// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

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
		class Collision : public Core::Component {
			public:
				Collision(void (*response)(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*));
				virtual ~Collision();

				virtual bool canAttach(Core::Entity&);
				void (*response)(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*);
		};
	}

	namespace CollisionResponse {
		void rigid_body(Core::Entity*, Core::Entity*, glm::vec3,  Core::GameObjects*);
		void static_body(Core::Entity*, Core::Entity*, glm::vec3,  Core::GameObjects*);
		void projectile(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*);

	}
}

#endif
