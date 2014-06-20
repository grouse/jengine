// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: main.cpp
// author: Jesper Stefansson
//
// Contains the entry point for the application, manages 
// initialisation of the engine and its attached systems.
//
// Once initialised, runs the main game loop and calls the
// update and handleInput functions in the engine

#include <iostream>

#include <SDL2/SDL.h>

#include "core/engine.h"

#include "systems/collision_system.h"
#include "systems/health_system.h"
#include "systems/life_time_system.h"
#include "systems/movement_system.h"
#include "systems/render_system.h"
#include "systems/audio_system.h"
#include "systems/input_system.h"

void player_fire();

void player_move_forward();
void player_move_left();
void player_move_back();
void player_move_right();

int main(int argc, char* argv[]) {
	GameObjects objects; 
	Engine engine(&objects);

	// set up the engine with systems
	InputSystem input(&engine, &objects);
	LifeTimeSystem life_time(&engine, &objects);
	MovementSystem movement(&engine, &objects);
	CollisionSystem collision(&engine, &objects);
	HealthSystem health(&engine, &objects);
	RenderSystem render(&engine, &objects);
	AudioSystem audio(&engine, &objects);
	
	engine.attachSystem(&input);
	engine.attachSystem(&life_time);
	engine.attachSystem(&movement);
	engine.attachSystem(&collision);
	engine.attachSystem(&health);
	engine.attachSystem(&render);
	engine.attachSystem(&audio);

	input.registerKeyEvent("Fire", KEY_PRESSED, &player_fire);
	
	input.registerKeyEvent("MoveForward", KEY_PRESSED, &player_move_forward);
	input.registerKeyEvent("MoveLeft", KEY_PRESSED, &player_move_left);
	input.registerKeyEvent("MoveBack", KEY_PRESSED, &player_move_back);
	input.registerKeyEvent("MoveRight", KEY_PRESSED, &player_move_right);
	


	if (engine.init() != 0)
		return -1;
	
	Uint32 old_time, current_time;
	current_time = SDL_GetTicks();

	float dt;

	while (engine.isRunning()) {
		old_time = current_time;
		current_time = SDL_GetTicks();

		// time since last frame in seconds
		dt = (current_time - old_time) / 1000.0f;

		// Handle the user input before any systems are updated
		engine.update(dt);		
	}
	
	return 0;
}

void player_fire() {
	std::cout << "FIRE" << std::endl;

}
void player_move_forward() {
	std::cout << "MovingForward" << std::endl;
}

void player_move_left() {
	std::cout << "MovingLeft" << std::endl;
}

void player_move_back() {
	std::cout << "MovingBack" << std::endl;
}

void player_move_right() {
	std::cout << "MovingRight" << std::endl;
}
