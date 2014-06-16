// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: movement_system.cpp
// author: Jesper Stefansson

#include "movement_system.h"

namespace JEngine {
	namespace Systems {
		MovementSystem::MovementSystem(Core::Engine* e, Core::GameObjects* o) :
		   Core::System(e, o) {}
		MovementSystem::~MovementSystem() {}

		void MovementSystem::init() {
			initialised = true;
		}

		void MovementSystem::update(float dt) {
			for (auto it = objects->components[Core::Component::VELOCITY].begin(); it != objects->components[Core::Component::VELOCITY].end(); it++) {

				Components::Velocity* v = (Components::Velocity*) (*it);
				Core::Entity* e = v->owner;;

				e->pos += v->vec3 * dt;
			}
		}
	}
}
