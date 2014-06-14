// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: velocity.cpp
// author: Jesper Stefansson

#include "velocity.h"

#include <iostream>

namespace JEngine {
	namespace Components {
		Velocity::Velocity(float x, float y, float z, float acceleration, float deacceleration, float max_speed) : Core::Component(Core::Component::VELOCITY), vec3(x, y, z) {

			this->acceleration = acceleration;
			this->deacceleration = deacceleration;
			this->max_speed = max_speed;

			rotation = 0;
		}

		Velocity::~Velocity() {}

		bool Velocity::canAttach(Core::Entity& e) {
			return true;
		}
	}
}
