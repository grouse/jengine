// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef VELOCITY_H
#define VELOCITY_H

#include <math.h>

#include <glm/vec3.hpp>

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {
		class Velocity : public Core::Component {
			public:
				Velocity(float, float, float, float, float, float);
				virtual ~Velocity();

				glm::vec3 vec3;

				virtual bool canAttach(Core::Entity&);

				float rotation;
				float acceleration, deacceleration, max_speed;

		};
	}
}

#endif
