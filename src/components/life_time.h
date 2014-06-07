// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef LIFE_TIME_H
#define LIFE_TIME_H

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {
		class LifeTime : public Core::Component {
			public:
				LifeTime(float);
				virtual ~LifeTime();

				virtual bool canAttach(Core::Entity&);

				float remaining;
		};
	}
}

#endif
