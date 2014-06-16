// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: movement_system.h
// author: Jesper Stefansson
//
// Contains the MovementSystem, which manages the entities
// with attached velocity components

#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/engine.h"
#include "core/game_objects.h"

#include "components/velocity.h"

namespace JEngine {
	namespace Systems {

		// See file comments for class details
		class MovementSystem : public Core::System {
			public:
				MovementSystem(Core::Engine*, Core::GameObjects*);
				~MovementSystem();

				virtual void init();

				// Iterates over the entities with an attached
				// Velocity component and updates the entity
				// position	
				virtual void update(float dt);
		};
	}
}

#endif
