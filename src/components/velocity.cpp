// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: velocity.cpp
// author: Jesper Stefansson

#include "velocity.h"

#include <iostream>

Velocity::Velocity(float x, float y, float z, float acceleration, float deacceleration, float max_speed) : 
	Component(ComponentId::VELOCITY), 
	vec3(x, y, z) {
	
	this->acceleration = acceleration;
	this->deacceleration = deacceleration;
	this->max_speed = max_speed;
}

Velocity::~Velocity() {}

bool Velocity::canAttach(Entity& e) {
	return true;
}
