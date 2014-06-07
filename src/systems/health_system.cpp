// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "health_system.h"

#include <iostream>

namespace JEngine {
	namespace Systems {
		HealthSystem::HealthSystem(Core::GameObjects* objects) : Core::System(objects) {}
		HealthSystem::~HealthSystem() {}

		void HealthSystem::init() { 
			initialised = true;
		}

		void HealthSystem::update(float dt) {
			for (auto it = objects->components[Core::Component::HEALTH].begin(); it != objects->components[Core::Component::HEALTH].end(); it++) {
				Components::Health* h = (Components::Health*) (*it);
				
				if (h->health <= 0) 
					objects->trashEntity(h->owner);
				
			}	
		}
	}
}
