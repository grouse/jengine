// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: damage.cpp
// author: Jesper Stefansson

#include "damage.h"

Damage::Damage(float dmg) : 
	Component(EComponentType::DAMAGE) {
	this->damage = dmg;
}

Damage::~Damage() {}
