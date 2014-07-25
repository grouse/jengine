// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.
//
// file: engine.cpp
// author: Jesper Stefansson


#include "engine.h"

Engine::Engine(GameObjects* objects) {
	this->objects = objects;
}

Engine::~Engine() {
	SDL_Quit();
}

int Engine::init() {

	// Initialise SDL with Video and Audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << SDL_GetError() << "\n";
	}

	// initialise the attached systems. 
	// TODO: implement a configuration/settings class
	for (auto it = systems.begin(); it != systems.end(); it++)
		(*it)->init();


	// Load the entities defined in data/entities file into objects
	// TODO: move out of engine class
	///Level::load("data/entities", objects);	
	
	run = true; // initialisation successful, so we are now ready to run the engine
	return 0; 	// TODO: return error/success code based on SDL_Init and Systems.init
}

void Engine::attachSystem(System* s) {
	systems.push_back(s);
}

void Engine::update(float dt) {
	delta_time = dt;

	// Update the attached systems
	for (auto it = systems.begin(); it != systems.end(); it++) {
		//std::cout << "updating system: " << (*it) << "\n";
		(*it)->update(dt);
	}

	// Process the GameObjects trash
	objects->processTrash();
}

void Engine::quit() {
	run = false;
}

bool Engine::isRunning() {
	return run;
}

float Engine::deltaTime() {
	return delta_time;
}
