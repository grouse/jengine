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

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/shape.h"
#include "components/texture.h"

// See file comments for class details
class RenderSystem : public System {
	public:
		RenderSystem(Engine*, GameObjects*);

		// Destroys the SDL window and OpenGL context
		virtual ~RenderSystem();

		// Creates the SDL window, OpenGL context with
		// the appropriate initialisations
		virtual void init();

		// Renders the entities with an attached Shape 
		// component, if entity also has a Texture 
		// component the texture is applied to the shape
		// with standard UV
		virtual void update(float);


		glm::vec3 camera;
	private:
		SDL_Window* window;			// The main application window
		SDL_GLContext glcontext;	// OpenGL context

		float uv[8];				// standard UV, to be replaced in future
};

#endif
