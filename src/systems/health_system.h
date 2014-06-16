// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: health_system.h
// author: Jesper Stefansson
//
// Contains the HealthSystem which manages the cleanup for all
// entities whose health go below 0

#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "core/component.h"
#include "core/entity.h"
#include "core/system.h"
#include "core/engine.h"
#include "core/game_objects.h"

#include "components/health.h"

namespace JEngine {
	namespace Systems {

		// See file comments for class details
		class HealthSystem : public Core::System {
			public:
				HealthSystem(Core::Engine*, Core::GameObjects*);
				virtual ~HealthSystem();

				virtual void init();

				// Goes through each entity with a health
				// component and puts them in the trash if 
				// the health value <= 0
				virtual void update(float dt);
		};
	}
}

#endif
