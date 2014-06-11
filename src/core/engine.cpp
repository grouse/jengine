// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "engine.h"

#include <math.h>


#include "stb_image.c"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>



static const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

namespace JEngine {
	namespace Core {
		void screenshot(int x, int y, int w, int h, const char* filename) {
			unsigned char* apixels = new unsigned char[w*h*4];
			glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, apixels);

			unsigned char* pixels = new unsigned char[w*h*4];
			for (unsigned int line = 0; line < h; line++) {
				unsigned int pos = line*w*4;
				for (unsigned int i = 0; i < w*4; i++) {
					pixels[pos+i] = apixels[(w*4*h-pos)-(w*4)+i];
				}

			}


			SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, w, h, 32, w*4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
			SDL_SaveBMP(surface, filename);

			SDL_FreeSurface(surface);
			delete[] pixels;
		}

		Engine::Engine(GameObjects* objects) {
			this->objects = objects;
			run = false;
		}

		Engine::~Engine() {
			for (auto it = systems.begin(); it != systems.end(); it++)
				delete (*it);

			SDL_Quit();
		}

		int Engine::init() {

			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
				std::cerr << SDL_GetError() << "\n";
			}

			for (auto it = systems.begin(); it != systems.end(); it++)
				(*it)->init();

			player = objects->pushEntity(new Entity(100.0f, 100.0f, 0.0f));

			objects->attachComponent(player, new Components::Shape({
				-16.0f, -16.0f, 0.0f,
				16.0f, -16.0f, 0.0f,
				16.0f, 16.0f, 0.0f,
				-16.0f, 16.0f, 0.0f		
			}));

			objects->attachComponent(player, new Components::Velocity(0.0f, 0.0f, 0.0f, 1000.0f, 2.0f, 400.0f));
			objects->attachComponent(player, new Components::Collision(CollisionResponse::rigid_body));;
			objects->attachComponent(player, new Components::Texture("assets/ship.png"));
			objects->attachComponent(player, new Components::Health(100.0f));

			Entity* target = objects->pushEntity(new Entity(200.0f, 200.0f, 0.0f));
		
			objects->attachComponent(target, new Components::Shape({
				-16.0f, -16.0f, 0.0f,
				16.0f, -16.0f, 0.0f,
				16.0f, 16.0f, 0.0f,
				-16.0f, 16.0f, 0.0f				
			}));
		
			objects->attachComponent(target, new Components::Collision(CollisionResponse::static_body));
			objects->attachComponent(target, new Components::Health(100.0f));


			Level::load("data/entities", objects);	
			run = true;
			return 0;
		}

		void Engine::attachSystem(System* s) {
			systems.push_back(s);
		}

		void Engine::handleInput(SDL_Event& e) {
			if (e.type == SDL_QUIT)
				quit();

			if (e.type == SDL_MOUSEMOTION) {
				Components::Shape* s = (Components::Shape*) player->components[Component::SHAPE];
			
				glm::vec3 mouse = glm::vec3(e.motion.x, e.motion.y, 0.0f);
				glm::vec3 direction = mouse - player->pos;
				
				float angle = atan2(direction.y, direction.x);
				s->setRotation(angle + PI/2);
			}	

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_w: 	
						input_w = true;
						break;

					case SDLK_s:
						input_s = true;
						break;

					case SDLK_a:
						input_a = true;
						break;

					case SDLK_d:
						input_d = true;
						break;
				}
			}

			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_p:
						screenshot(0, 0, 1280, 720, "screenshot.bmp");
						break;

					case SDLK_w:
						input_w = false;
						break;

					case SDLK_s:
						input_s = false;
						break;

					case SDLK_a:
						input_a = false;
						break;

					case SDLK_d:
						input_d = false;
						break;

					case SDLK_y:
						Entity* t20;
						t20	= objects->pushEntity(new Entity(player->pos + glm::vec3(50.0f, 50.0f, 0.0f)));
			
						objects->attachComponent(t20, new Components::Shape({
							-16.0f, -16.0f, 0.0f,
							16.0f, -16.0f, 0.0f,
							16.0f, 16.0f, 0.0f,
							-16.0f, 16.0f, 0.0f		
						}));
					
						objects->attachComponent(t20, new Components::Collision(CollisionResponse::static_body));
						objects->attachComponent(t20, new Components::Health(100.0f));
						break;

					case SDLK_f:
						glm::vec3 rotation = glm::rotateZ(glm::vec3(1.0f, 0.0f, 0.0f), (float)(((Components::Shape*) player->components[Component::SHAPE])->rotation - PI/2.0f));
						glm::vec3 pos = player->pos + rotation*25.0f;

						Entity* projectile = objects->pushEntity(new Entity(pos));
							
						Components::Shape* p_shape = new Components::Shape({
							-4.0f, -4.0f, 0.0f,
							4.0f, -4.0f, 0.0f,
							4.0f, 4.0f, 0.0f,
							-4.0f, 4.0f, 0.0f		
						});

						p_shape->rotate(((Components::Shape*) player->components[Component::SHAPE])->rotation);

						objects->attachComponent(projectile, p_shape);

						objects->attachComponent(projectile, new Components::Velocity(rotation.x*1000, rotation.y*1000, 0.0f, 1.0f, 0.0f, 100.0f));
						objects->attachComponent(projectile, new Components::Collision(CollisionResponse::projectile));
						objects->attachComponent(projectile, new Components::Texture("assets/projectile.png"));
						objects->attachComponent(projectile, new Components::Damage(40.0f));
						objects->attachComponent(projectile, new Components::LifeTime(300));
					
						break;
				}
			}
		}

		void Engine::update(float dt) {

			
			Components::Velocity* v = (Components::Velocity*) player->components[Core::Component::VELOCITY];
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
			}


			for (auto it = systems.begin(); it != systems.end(); it++)
				(*it)->update(dt);

			objects->processTrash();
		}

		void Engine::quit() {
			run = false;
		}

		bool Engine::isRunning() {
			return run;
		}
	}
}
