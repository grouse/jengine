#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "core/component.h"
#include "core/entity.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/health.h"


namespace JEngine {
	class HealthSystem : public System {
		public:
			HealthSystem(GameObjects*);
			virtual ~HealthSystem();

			virtual void update(float dt);
	};
}

#endif
