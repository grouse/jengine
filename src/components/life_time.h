// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: life_time.h
// author: Jesper Stefansson
//
// Contains the LifeTime component which is used primarly by
// the projectile component to ensure that projectile entities
// are discarded after a certain period of time

#ifndef LIFE_TIME_H
#define LIFE_TIME_H

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {

		// See file comments for class details
		class LifeTime : public Core::Component {
			public:
				LifeTime(float);
				virtual ~LifeTime();

				// Returns true, LifeTime currently does not
				// depend on any other component
				virtual bool canAttach(Core::Entity&);

				// Time in seconds until the parent entity should
				// be discarded 
				float remaining;
		};
	}
}

#endif
