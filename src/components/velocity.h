// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: velocity.h
// author: Jesper Stefansson
//
// Contains the Velocity component which contains the data necessary
// to model velocity, direction, acceleration, and max speed

#ifndef VELOCITY_H
#define VELOCITY_H

#include <math.h>

#include <glm/vec3.hpp>

#include "core/entity.h"
#include "core/component.h"

// See file comments for class details
class Velocity : public Component {
	public:

		// Params: initial velocity (x, y, z), acceleration, deacceleration, max speed
		Velocity(float, float, float, float, float, float);
		virtual ~Velocity();

		glm::vec3 vec3; // velocity
		float acceleration, deacceleration, max_speed;
		float accelerateForward = 0.0f, accelerateSide = 0.0f;

};

#endif
