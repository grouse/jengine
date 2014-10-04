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

	input.init();
	physics.init(glm::vec3(0.0f, 100.0f, 0.0f));
	render.init();

	GameState::running = true;	
	return 0; 	// TODO: return error/success code based on SDL_Init and Systems.init
}

void Engine::update(float dt) {
	delta_time = dt;

	input.update();
	physics.update(dt);
	render.update(dt);
}

void Engine::quit() {
	run = false;
}

float Engine::deltaTime() {
	return delta_time;
}
