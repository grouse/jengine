#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/velocity.h"

namespace JEngine {

	class MovementSystem : public System {
		public:
			MovementSystem(GameObjects*);
			~MovementSystem();

			virtual void update(float dt);
	};
}

#endif
