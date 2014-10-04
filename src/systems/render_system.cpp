// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: render_system.cpp
// author: Jesper Stefansson

#include "render_system.h"

#include <iostream>

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(glcontext);
}

void RenderSystem::init() {
	// Window width, height and title
	// TODO: Replace with configuration
	int w = 1280, h = 720;
	const char* title = "JEngine";

	// Create an SDL window at any screen position,
	// SDL_WINDOW_OPENGL to let SDL know we plan to
	// use OpenGL for renderig
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w,
		h,
		SDL_WINDOW_OPENGL		
	);

	if (window == NULL) {
		std::cerr << SDL_GetError() << "\n";
		SDL_Quit();
	}

	glcontext = SDL_GL_CreateContext(window);
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Set OpenGL viewport
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderSystem::update(float dt) {
	// Start by clearing the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(-camera.x, -camera.y, -camera.z);
	
	for (unsigned int i = 0; i < components.mesh.next; i++) {
		unsigned int entity = components.mesh.cmp_ent_id[i];
		Position* p = components.position.getCmpFrom(entity);;

		glTranslatef(p->x, p->y, p->z);

		glVertexPointer(3, GL_FLOAT, 0, components.mesh[i].vertices.data());
		glColor3f(255, 255, 255);
		glDrawArrays(GL_QUADS, 0, 4);
		
		glTranslatef(-p->x, -p->y, -p->z);
	}

	/**for (auto it = objects->components[EComponentType::SHAPE].begin(); it != objects->components[EComponentType::SHAPE].end(); it++) {
		Shape* s = (Shape*) (*it);
		Entity* e = s->owner;


		// Translate to entity position
		glTranslatef(e->pos.x, e->pos.y, e->pos.z);

		// Pass the vertex data to OpenGL
		// TODO: Replace with VBO
		glVertexPointer(
			3, GL_FLOAT, 0,
			s->vertices.data()
		);
		
		// If the entity has a texture we should bind the texture in OpenGL
		// and pass the UV coordinates
		if (e->components[EComponentType::TEXTURE] != 0) {
			Texture* t = (Texture*) e->components[EComponentType::TEXTURE];

			// Bind texture
			glBindTexture(GL_TEXTURE_2D, t->GLtex);

			// Pass the default UV coordinates
			// TODO: Replace with UV in VBO
			glTexCoordPointer(2, GL_FLOAT, 0, t->uv.data());

			// Draw the shape with texture
			glDrawArrays(GL_QUADS, 0, 4);

			// Unbind texture in OpenGL
			glBindTexture(GL_TEXTURE_2D, 0);
		} else { // Otherwise we just draw a flat white colour
			glColor3f(255, 255, 255);

			// Draw the shape with the flat colour
			glDrawArrays(GL_QUADS, 0, 4);
		}

		// Translate back to (0, 0, 0)
		glTranslatef(-e->pos.x, -e->pos.y, -e->pos.z);
	}**/
	
	// Flip the framebuffers
	SDL_GL_SwapWindow(window);
}
