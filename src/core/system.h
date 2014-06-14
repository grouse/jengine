// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: system.h
// author: Jesper Stefansson
//
// Contains the System class which acts as the base class for
// all engine systems, located in src/systems.
//
// System acts as a purely virtual class with declared functions
// that each system must define, such as init and update 

#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <list>

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"

namespace JEngine {
	namespace Core {

		// See file comments for class details
		class System {
			public:
				System(GameObjects* o) {objects = o;};

				virtual void init() = 0;		// initialise system
				virtual void update(float) = 0;	// update system, paramter is seconds since last frame

			protected:
				bool initialised = false;
				GameObjects* objects;
				

		};
	}
}

#endif
