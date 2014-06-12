// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

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

// Class used for loading entities from file, the format for
// each line should be ID DATA where ID is the Component ID as 
// represented by const integers in Core::Component, and DATA 
// is space separated values for the component.
namespace JEngine {
	namespace Core {
		
		class Level {
		public:

			// Loads entities into GameObjects from file
			static void load(const char*, Core::GameObjects*);
		};
	}
}

#endif
