// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: level.h
// author: Jesper Stefansson
//
// Contains functions to load components from string input and
// attach them to an entity. 

#ifndef LEVEL_H
#define LEVEL_H

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"

#include "components/collision.h"
#include "components/damage.h"
#include "components/health.h"
#include "components/life_time.h"
#include "components/shape.h"
#include "components/texture.h"
#include "components/velocity.h"

namespace JEngine {
	namespace Core {
		
		// See file comments for class details
		class Level {
		public:

			// Loads entities into GameObjects from file
			//
			// Each line in the file should begin with a new 
			// entitiy's position and proceeded by the component data
			// for the commponents that should be attached to the entity
			static void load(const char*, Core::GameObjects*);
		};
	}
}

#endif
