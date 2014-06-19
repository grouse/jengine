// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: engine.h
// author: Jesper Stefansson
//
// Contains the Engine class which handles all attached systems, input
// and memory management. The engine is ignorant to which systems are 
// attached and simply contains a list of pointers to the systems,
// by calling Engine::update(float) the engine will update all 
// attached systems and finish with processing the GameObjects trash.
//
// Sample usage:
// 		Engine e;
// 		e.attachSystem(new System(&GameObjects));
// 		e.init();
//
// 		while (e.isRunning())
// 			e.handleInput(SDL_Event);
// 			e.update(dt);
#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <list>
#include <vector>

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"
#include "core/level.h"
#include "core/system.h"

#include "components/shape.h"
#include "components/velocity.h"
#include "components/collision.h"
#include "components/life_time.h"
#include "components/texture.h"
#include "components/health.h"
#include "components/damage.h"


// See file comments for class details
class Engine {
	public:
		// Saves the GameObjects pointer 	
		Engine(GameObjects*);

		// Deallocates all attached systems and call SDL_Quit()
		//
		// Function is equivalent to:
		// 		for (system : systems)
		// 			delete system;
		// 		SDL_Quit();
		virtual ~Engine();

		// Initialises SDL and the attached systems
		//
		// Function is equivalent to:
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

#endif // ENGINE_H
