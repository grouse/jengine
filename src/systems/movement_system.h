#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/velocity.h"

namespace JEngine {
	namespace Systems {

		class MovementSystem : public Core::System {
			public:
				MovementSystem(Core::GameObjects*);
				~MovementSystem();

				virtual void init();
				virtual void update(float dt);
		};
	}
}

#endif
