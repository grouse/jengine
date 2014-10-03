// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.
//
// file: engine.cpp
// author: Jesper Stefansson


#include "engine.h"

Engine engine;

Engine::Engine() {
}

Engine::~Engine() {
	SDL_Quit();
}

int Engine::init() {

	// Initialise SDL with Video and Audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << SDL_GetError() << "\n";
	}	

	run = true; // initialisation successful, so we are now ready to run the engine
	return 0; 	// TODO: return error/success code based on SDL_Init and Systems.init
}

void Engine::update(float dt) {
	delta_time = dt;
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
