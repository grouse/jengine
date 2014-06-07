// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "core/component.h"
#include "core/entity.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/health.h"


namespace JEngine {
	namespace Systems {
		class HealthSystem : public Core::System {
			public:
				HealthSystem(Core::GameObjects*);
				virtual ~HealthSystem();

				virtual void init();
				virtual void update(float dt);
		};
	}
}

#endif
