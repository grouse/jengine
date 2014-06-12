// Copyright (c) 2014 Jesper Stefansson. All rights reserved.

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <list>
#include <vector>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"
#include "core/level.h"

#include "systems/movement_system.h"
#include "systems/collision_system.h"
#include "systems/render_system.h"
#include "systems/life_time_system.h"
#include "systems/health_system.h"

#include "components/shape.h"
#include "components/velocity.h"
#include "components/collision.h"
#include "components/life_time.h"
#include "components/texture.h"
#include "components/health.h"
#include "components/damage.h"


namespace JEngine {
	namespace Core {

		// The engine class acts as a container for its attached systems 
		// which it initialises, updates, and manages. 
		//
		// Sample usage: 
		// 		Engine e;
		//		e.attachSystem(new System(GamaObjects*));
		//		e.init();
		//
		//		while (true)
		//			e.handleInput(SDL_Event);
		//			e.update(dt);
		class Engine {
			public:
				Engine(GameObjects*);
				virtual ~Engine();

				// Initialises SDL and the attached systems
				//
				// The function is equivalent to:
				//		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
				// 		for (system : systems)
				// 			system->init()
				int init();

				// Switch-cases the passed SDL_Event and determines what
				// logic to execute.
				void handleInput(SDL_Event&);

				// Attaches a system to the engine.
				//
				// The function is equivalent to:
				// 		systems.push_back(system);
				void attachSystem(System*);

				// Iterates over the attached system and calls its update
				// function. Also calls the processTrash function of
				// GameObjects.
				//
				// The paramater is expected to be the time-step in seconds
				// since last update.
				//
				// Function is equivalent to:
				// 		for (system : systems)
				// 			system->update(dt);
				//
				// 		GameObjects->processTrash();
				void update(float);

				// Sets the run variable to false, indicating that the
				// engine should exit at the next while check.
				//
				// Sample usage:
				// 		if (SomeCondition)
				// 			e->quit();
				void quit();

				// returns run
				//
				// Sample usage:
				// 		if (e->isRunning())
				// 			SomeOperation();
				bool isRunning();

			private:
				// Flag set to true in Engine::init() and is set to false
				// by calling Engine::quit(). Intended usage is for the
				// condition in the game loop from which the engine is run.
				bool run = false;

				// Pointer to GameObjects, which contains all entities 
				// and components.
				GameObjects* objects;

				// List container for the attached systems. Added to by
				// Engine::attachSystem(System*) and iterated over by
				// Engine::update(float);
				std::list<System*> systems;

				// Pointer to the player object of the game
				Entity* player;

				// Input flags to determine which direction to apply thrust 
				// to the player object.
				bool input_w = false, input_s = false, input_a = false, input_d = false;
		};
	}
}

#endif // ENGINE_H
