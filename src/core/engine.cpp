// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.
//
// file: engine.cpp
// author: Jesper Stefansson


#include "engine.h"

#include <math.h>
#include <iostream>


#include "stb_image.c"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>



static const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

// Saves a BMP screenshot of the currently displayed pixels
void screenshot(int x, int y, int w, int h, const char* filename) {
	unsigned char* apixels = new unsigned char[w*h*4];
	glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, apixels);

	unsigned char* pixels = new unsigned char[w*h*4];

	// glReadPixels will start at bottom-left, our coordinate system starts
	// at top-left, so reverse the rows.
	for (unsigned int line = 0; line < h; line++) {
		unsigned int pos = line*w*4;
		for (unsigned int i = 0; i < w*4; i++) {
			pixels[pos+i] = apixels[(w*4*h-pos)-(w*4)+i];
		}

	}

	// Render pixels to an SDL_Surface, then save surface to file
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, w, h, 32, w*4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
	SDL_SaveBMP(surface, filename); 

	// Cleanup
	SDL_FreeSurface(surface);
	delete[] pixels;
}

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


// TODO: implement InputSystem and move the entirety of this function into its 
// update function. Input events will then be thrown by registering call back 
// function pointers.
void Engine::handleInput(SDL_Event& e) {
/**
				Entity* t20;

				// The target is spawned slightly away from the player
				t20	= objects->pushEntity(new Entity(player->pos + glm::vec3(50.0f, 50.0f, 0.0f)));
	
				// 32x32 pixel shape
				objects->attachComponent(t20, new Shape({
					-16.0f, -16.0f, 0.0f,
					16.0f, -16.0f, 0.0f,
					16.0f, 16.0f, 0.0f,
					-16.0f, 16.0f, 0.0f		
				}));
			
				objects->attachComponent(t20, new Collision(CollisionResponse::static_body));
				objects->attachComponent(t20, new Health(100.0f));
			// Spawn static target with collision and health component
			case SDLK_y: 
				break;

			// Shoot projectile originating from player with same rotation as the player's shape
			case SDLK_f: 
			
				break;
		}
	}**/
}

void Engine::update(float dt) {
	delta_time = dt;

	// Apply thrust in the direction determined by which keys (WASD) are
	// pressed.
	// TODO: Shouldn't be here, should be in handleInput. Will be stay until
	// implementation of InputSystem, after which it will be removed from the
	// engine class entirely.
	
	/**Components::Velocity* v = (Components::Velocity*) player->components[Core::Component::VELOCITY];
	Components::Shape* s = (Components::Shape*) player->components[Core::Component::SHAPE];

	if (input_w || input_a || input_s || input_d) {
		glm::vec3 thrust;

		if (input_a && input_s) {
			thrust = glm::vec3(-1.0f, 1.0f, 0.0f);
		} else if (input_a && input_w) {
			thrust = glm::vec3(-1.0f, -1.0f, 0.0f);
		} else if (input_d && input_s) {
			thrust = glm::vec3(1.0f, 1.0f, 0.0f);
		} else if (input_d && input_w) {
			thrust = glm::vec3(1.0f, -1.0f, 0.0f);
		} else if (input_a) {
			thrust = glm::vec3(-1.0f, 0.0f, 0.0f);
		} else if (input_d) {
			thrust = glm::vec3(1.0f, 0.0f, 0.0f);
		} else if (input_s) {
			thrust = glm::vec3(0.0f, 1.0f, 0.0f);
		} else if (input_w) {
			thrust = glm::vec3(0.0f, -1.0f, 0.0f);
		}

		thrust = glm::normalize(thrust);
		thrust = glm::rotateZ(thrust, s->rotation);

		v->vec3 += thrust*v->acceleration*dt;

	} else {
		glm::vec3 new_v = v->vec3 - v->vec3*v->deacceleration*dt;

		if (glm::length(new_v) >= glm::length(v->vec3)) {
			v->vec3 = glm::vec3(0.0f);
		} else {
			v->vec3 = new_v;	
		}
	} **/

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
