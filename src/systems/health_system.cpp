// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: health_system.cpp
// author: Jesper Stefansson

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
