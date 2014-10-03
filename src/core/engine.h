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


// See file comments for class details
class Engine {
	public:
		// Saves the GameObjects pointer 	
		Engine();

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

		// Returns the delta_time variable
		float deltaTime();

	private:
		// Flag set to true in Engine::init() and is set to false
		// by calling Engine::quit(). Intended usage is for the
		// condition in the game loop from which the engine is run.
		bool run = false;

		// Updated by Engine::update and used by various parts of the
		// program to access the time since last frame update.
		float delta_time = 0.0f;
};

#endif // ENGINE_H
