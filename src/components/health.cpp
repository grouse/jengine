// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: health.cpp
// author: Jesper Stefansson

#include "health.h"

Health::Health(float hp) : Component(ComponentId::HEALTH) {
	this->health = hp;
}

Health::~Health() {}
