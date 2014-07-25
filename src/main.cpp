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
#include "core/entity.h"
#include "core/component.h"

#include "systems/collision_system.h"
#include "systems/health_system.h"
#include "systems/life_time_system.h"
#include "systems/physics_system.h"
#include "systems/render_system.h"
#include "systems/audio_system.h"
#include "systems/input_system.h"

#include "components/shape.h"
#include "components/velocity.h"
#include "components/collision.h"
#include "components/texture.h"
#include "components/health.h"

GameObjects objects;
Engine engine(&objects);
	
InputSystem input(&engine, &objects);
LifeTimeSystem life_time(&engine, &objects);
PhysicsSystem physics(&engine, &objects);
CollisionSystem collision(&engine, &objects);
HealthSystem health(&engine, &objects);
RenderSystem render(&engine, &objects);
AudioSystem audio(&engine, &objects);

void game_reset();

Entity* player;

float player_turn_at_rate = 5.0f;

float player_acceleration = 750.f;
float player_deacceleration = 750.f;
float player_max_speed = 1000.0f;

void player_fire();

void player_move_forward(float);
void player_move_right(float);

void player_turn(float);

void init_player();

int main(int argc, char* argv[]) {
	// set up the engine with systems	
	engine.attachSystem(&input);
	engine.attachSystem(&life_time);
	engine.attachSystem(&physics);
	engine.attachSystem(&collision);
	engine.attachSystem(&health);
	engine.attachSystem(&render);
	engine.attachSystem(&audio);

	if (engine.init() != 0)
		return -1;
	
	init_player();

	input.bindAction("Reset", KEY_RELEASED, &game_reset);
	
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

void game_reset() {
	player->pos = glm::vec3(0.0f, 0.0f, 0.0f);
	((Shape*) player->components[ComponentId::SHAPE])->setRotation(0.0f);
}

void player_fire() {
	std::cout << "FIRE" << std::endl;
}

void player_move_forward(float value) {
	Velocity* v = (Velocity*) player->components[ComponentId::VELOCITY];
	v->accelerateForward = value;
}

void player_move_right(float value) {
	Velocity* v = (Velocity*) player->components[ComponentId::VELOCITY];
	v->accelerateSide = value;
}

void player_turn(float value) {
	physics.addRotation(player, value*player_turn_at_rate);
}

void init_player() {
	// bind appropriate key and axis events to player functions
	input.bindAction("Fire", KEY_PRESSED, &player_fire);
	
	input.bindAxis("MoveForward", &player_move_forward);
	input.bindAxis("MoveRight", &player_move_right);
	input.bindAxis("Turn", &player_turn);

	// Create the player object
	// TODO: implement InputSystem so that player initialisation can be
	// handled outside of the engine class
	player = objects.pushEntity(new Entity(100.0f, 100.0f, 0.0f));

	// Creates a 32x32 pixels wide/high square with origin in center.
	objects.attachComponent(player, new Shape({
		-16.0f, -16.0f, 0.0f,
		16.0f, -16.0f, 0.0f,
		16.0f, 16.0f, 0.0f,
		-16.0f, 16.0f, 0.0f		
	}));

	// Creates velocity component with acceleration of 1000, deacceleration of 
	// 2 and max speed of 400, units are pixels/second
	objects.attachComponent(player, new Velocity(0.0f, 0.0f, 0.0f, player_acceleration, player_deacceleration, player_max_speed));

	objects.attachComponent(player, new Collision(CollisionResponse::rigid_body));;
	objects.attachComponent(player, new Texture("assets/ship.png"));
	objects.attachComponent(player, new Health(100.0f));
}
