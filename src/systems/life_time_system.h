// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: life_time_system.h
// author: Jesper Stefansson
//
// Contains the LifeTimeSystem, which manages each entity with
// an attached LifeTime component, putting it in the trash if 
// its lifetime is up

#ifndef LIFE_TIME_SYSTEM_H
#define LIFE_TIME_SYSTEM_H

#include <list>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/life_time.h"

// See file comments for class details
class LifeTimeSystem : public System {
public:
	LifeTimeSystem(Engine*, GameObjects*);
	virtual ~LifeTimeSystem();

	virtual void init();

	// Iterates over all entities with an attached
	// LifeTime component and places it in the trash
	// if its lifetime value <= 0
	// Additionally, subtracts dt from the lifetime 
	// value
	virtual void update(float);

};

#endif
