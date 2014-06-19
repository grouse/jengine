// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: life_time.cpp
// author: Jesper Stefansson

#include "life_time.h"

LifeTime::LifeTime(float t) : 
	Component(ComponentId::LIFETIME) {
	remaining = t;
}

LifeTime::~LifeTime() {}

bool LifeTime::canAttach(Entity& e) {
	return true;
}	
