// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: health.h
// author: Jesper Stefansson
//
// Contains the Health component, which contains nothing more
// than the amount of health has. Health is currently only 
// deducted by the projectile collision response.
#ifndef HEALTH_H
#define HEALTH_H

#include "core/entity.h"
#include "core/component.h"

// See file comments for class details
class Health : public Component {
	public:
		Health(float hp);
		virtual ~Health();

		// The health of the entity, when it reaches 0
		// the entity is cleaned up and deleted
		float health;
};

#endif
