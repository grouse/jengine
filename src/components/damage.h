// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: damage.h
// author: Jesper Stefansson
//
// Contains the Damage component, which contains nothing more
// than the amount of damage the entity should do. Damage
// is currently only used by the projectile collision response

#ifndef DAMAGE_H
#define DAMAGE_H

#include "core/entity.h"
#include "core/component.h"

// See file comments for class details
class Damage : public Component {
	public:
		Damage(float);
		virtual ~Damage();
		
		// Returns true, Damage currently does not depend
		// on any other component
		virtual bool canAttach(Entity&);

		// The damage to inflict upon the other entity when
		// triggerd
		float damage;
};

#endif
