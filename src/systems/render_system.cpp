// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "render_system.h"

#include <iostream>

namespace JEngine {
	namespace Systems {

		RenderSystem::RenderSystem(Core::GameObjects* objects) : Core::System(objects) {

			uv[0] = 0.0f;
			uv[1] = 0.0f;

			uv[2] = 1.0f;
			uv[3] = 0.0f;

			uv[4] = 1.0f;
			uv[5] = 1.0f;

			uv[6] = 0.0f;
			uv[7] = 1.0f;

		}

		RenderSystem::~RenderSystem() {
			SDL_DestroyWindow(window);
			SDL_GL_DeleteContext(glcontext);
		}

		void RenderSystem::init() {
			int w = 1280, h = 720;
			const char* title = "JEngine";

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
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			// Set viewport

			glViewport(0, 0, (GLsizei)w, (GLsizei)h);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();


			initialised = true;
		}

		void RenderSystem::update(float dt) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			for (auto it = objects->components[Core::Component::SHAPE].begin(); it != objects->components[Core::Component::SHAPE].end(); it++) {
				Components::Shape* s = (Components::Shape*) (*it);
				Core::Entity* e = s->owner;

				glLoadIdentity();
				glTranslatef(e->pos.x, e->pos.y, e->pos.z);


				glVertexPointer(
					3, GL_FLOAT, 0,
					s->vertices.data()
				);
				
				if (e->components[Core::Component::TEXTURE] != 0) {
					Components::Texture* t = (Components::Texture*) e->components[Core::Component::TEXTURE];
					glBindTexture(GL_TEXTURE_2D, t->GLtex);
					glTexCoordPointer(2, GL_FLOAT, 0, uv);

					glDrawArrays(GL_QUADS, 0, 4);
					glBindTexture(GL_TEXTURE_2D, 0);
				} else {
					glColor3f(255, 255, 255);
					glDrawArrays(GL_QUADS, 0, 4);
				}

				
				glTranslatef(-e->pos.x, -e->pos.y, -e->pos.z);
			}
			
			SDL_GL_SwapWindow(window);
		}
	}
}
