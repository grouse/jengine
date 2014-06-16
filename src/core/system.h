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
		class Engine;

		// See file comments for class details
		class System {
			public:
				System(Engine* e, GameObjects* o) {
					engine = e;
					objects = o;
				};

				virtual ~System() {}

				virtual void init() = 0;		// initialise system
				virtual void update(float) = 0;	// update system, paramter is seconds since last frame

			protected:
				bool initialised = false;

				Engine* engine;
				GameObjects* objects;
				

		};
	}
}

#endif
