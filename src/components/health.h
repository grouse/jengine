// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: health.h
// author: Jesper Stefansson
//
// Contains the Health component, which contains nothing more
// than the amount of health has. Health is currently only 
// deducted by the projectile collision response.
#ifndef HEALTH_H
#define HEALTH_H

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {

		// See file comments for class details
		class Health : public Core::Component {
			public:
				Health(float);
				virtual ~Health();

				// Returns true, the component currently does
				// not depend on any other component
				virtual bool canAttach(Core::Entity&);
				
				// The health of the entity, when it reaches 0
				// the entity is cleaned up and deleted
				float health;
		};
	}
}

#endif
