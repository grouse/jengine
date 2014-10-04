// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: render_system.h
// author: Jesper Stefansson
//
// Contains the RenderSystem, which handles all OpenGL render
// calls and initialisation of the OpenGL contexts and SDL 
// windows

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "ecs/components.hpp"
#include "ecs/component_manager.h"
#include "ecs/entity_manager.h"

// See file comments for class details
class RenderSystem {
	public:
		RenderSystem();

		// Destroys the SDL window and OpenGL context
		~RenderSystem();

		// Creates the SDL window, OpenGL context with
		// the appropriate initialisations
		void init();

		// Renders the entities with an attached Shape 
		// component, if entity also has a Texture 
		// component the texture is applied to the shape
		// with standard UV
		void update(float);


		glm::vec3 camera = glm::vec3(0.0f, 0.0f, 0.0f);
	private:
		SDL_Window* window;			// The main application window
		SDL_GLContext glcontext;	// OpenGL context
};

#endif
