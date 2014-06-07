// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef LIFE_TIME_SYSTEM_H
#define LIFE_TIME_SYSTEM_H

#include <list>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"

#include "components/life_time.h"

namespace JEngine {
	namespace Systems {
		class LifeTimeSystem : public Core::System {
			public:
				LifeTimeSystem(Core::GameObjects*);
				virtual ~LifeTimeSystem();

				virtual void init();
				virtual void update(float);

		};
	}
}

#endif
