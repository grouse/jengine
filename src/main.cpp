// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
// 
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

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "core/engine.h"
#include "core/entity.h"
#include "core/component.h"
#include "core/level.h"

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
#include "components/life_time.h"
#include "components/damage.h"
#include "components/physics_body.h"

static const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

GameObjects objects;
Engine engine(&objects);
	
InputSystem input(&engine, &objects);
LifeTimeSystem life_time(&engine, &objects);
PhysicsSystem physics(&engine, &objects,glm::vec3(0.0f,0.0f,0.0f));
CollisionSystem collision(&engine, &objects);
HealthSystem health(&engine, &objects);
RenderSystem render(&engine, &objects);
AudioSystem audio(&engine, &objects);

void game_reset();
void game_movecamera_x(float);
void game_movecamera_y(float);

Entity* player;

float player_turn_at_rate = 5.0f;

float player_acceleration = 750.f;
float player_deacceleration = 0.f;
float player_max_speed = 1000.0f;

void player_fire();
void player_jump();

void player_move_forward(float);
void player_move_right(float);

void player_turn(float);
void player_turn_at(float);

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

	Level::load("data/map", &objects);

	input.bindAction("Reset", KEY_RELEASED, &game_reset);
	input.bindAxis("CameraX", &game_movecamera_x);
	input.bindAxis("CameraY", &game_movecamera_y);
	
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
	((Shape*) player->components[EComponentType::SHAPE])->setRotation(0.0f);
}

void game_movecamera_x(float value) {
	render.camera.x += value*5.0f;
}

void game_movecamera_y(float value ) {
	render.camera.y += value*5.0f;
}

void player_jump() {
	Velocity* v = (Velocity*) player->components[EComponentType::VELOCITY];
	v->vec3.y = -200.0f;
}

void player_fire() {
	// The rotation of the projectile should be equal to that of the player's
	glm::vec3 rotation = glm::rotateZ(glm::vec3(1.0f, 0.0f, 0.0f), (float)(((Shape*) player->components[EComponentType::SHAPE])->rotation - PI/2.0f));
	// Spawn the projectile infront of the player
	// TODO: Implement an anchor system with coordinates relative to player's center
	glm::vec3 pos = player->pos + rotation*25.0f;

	Entity* projectile = objects.pushEntity(new Entity(pos));
		
	// 8x8 square
	Shape* p_shape = new Shape({
		-4.0f, -4.0f, 0.0f,
		4.0f, -4.0f, 0.0f,
		4.0f, 4.0f, 0.0f,
		-4.0f, 4.0f, 0.0f		
	});

	// Rotate the projectile's shape to fit the rotation of the player
	p_shape->rotate(((Shape*) player->components[EComponentType::SHAPE])->rotation);
	objects.attachComponent(projectile, p_shape);

	// The direction of the projectile's velocity should be same as the projectile's rotation
	Velocity* p_vel = new Velocity(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 100.0f);
	Velocity* player_vel = (Velocity*) player->components[EComponentType::VELOCITY];

	p_vel->vec3 = 1000.0f*rotation + player_vel->vec3;

	objects.attachComponent(projectile, p_vel);
	


	objects.attachComponent(projectile, new Collision(CollisionResponse::projectile));
	objects.attachComponent(projectile, new Texture("assets/projectile.png", {
		0.0f, 0.0f, 
		8.0f, 0.0f, 
		8.0f, 8.0f, 
		0.0f, 8.0f	
	}));

	objects.attachComponent(projectile, new Damage(40.0f));
	
	// In case the projectile doesn't hit anything, destroy projectile after 300 seconds.
	objects.attachComponent(projectile, new LifeTime(300));
}

void player_move_forward(float value) {
	Velocity* v = (Velocity*) player->components[EComponentType::VELOCITY];
	v->vec3.y = value*100.0f;
	//v->accelerateForward = value;
}

void player_move_right(float value) {
	Velocity* v = (Velocity*) player->components[EComponentType::VELOCITY];
	v->vec3.x = value*100.0f;
	//v->accelerateSide = value;
}

void player_turn(float value) {
	physics.addRotation(player, value*player_turn_at_rate);
}

void player_turn_at(float value) {
	Shape* s = (Shape*) player->components[EComponentType::SHAPE];
	s->rotate(value*player_turn_at_rate*engine.deltaTime());
}

void init_player() {
	// bind appropriate key and axis events to player functions
	input.bindAction("Fire", KEY_PRESSED, &player_fire);
	input.bindAction("Jump", KEY_PRESSED, &player_jump);
	
	input.bindAxis("MoveForward", &player_move_forward);
	input.bindAxis("MoveRight", &player_move_right);
	input.bindAxis("Turn", &player_turn);
	//input.bindAxis("TurnAt", &player_turn_at);

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
    objects.attachComponent(player, new PhysicsBody(true));

	// Creates velocity component with acceleration of 1000, deacceleration of 
	// 2 and max speed of 400, units are pixels/second
	objects.attachComponent(player, new Velocity(0.0f, 0.0f, 0.0f, player_acceleration, player_deacceleration, player_max_speed));

	objects.attachComponent(player, new Collision(CollisionResponse::rigid_body));;

	objects.attachComponent(player, new Texture("assets/ship.tiled.png", {
		0.0f, 0.0f,
		32.0f, 0.0f,
		32.0f, 32.0f,
		0.0f, 32.0f
	}));
	
	objects.attachComponent(player, new Health(100.0f));
}
