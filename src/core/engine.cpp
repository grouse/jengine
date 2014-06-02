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

		Engine::Engine() {
			run = false;
			window = NULL;
		}

		Engine::~Engine() {
			SDL_DestroyWindow(window);
			SDL_GL_DeleteContext(glcontext);
			SDL_Quit();

			for (auto it = systems.begin(); it != systems.end(); it++)
				delete (*it);

			delete objects;
		}

		int Engine::init(const char* title, int w, int h) {

			if (SDL_Init(SDL_INIT_VIDEO) != 0) {
				std::cerr << SDL_GetError() << "\n";
				return -1;
			}

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
				return -1;
			}

			initGL(w, h);

			objects = new GameObjects();
			system = new System(objects);

			systems.push_back(system);
			systems.push_back(new Systems::LifeTimeSystem(objects));
			systems.push_back(new Systems::MovementSystem(objects));
			systems.push_back(new Systems::CollisionSystem(objects));
			systems.push_back(new Systems::HealthSystem(objects));
			systems.push_back(new Systems::RenderSystem(objects, window));

			
			player = objects->pushEntity(new Entity(100.0f, 100.0f, 0.0f));

			float p_verts[] = {
				-16.0f, -16.0f, 0.0f,
				16.0f, -16.0f, 0.0f,
				16.0f, 16.0f, 0.0f,
				-16.0f, 16.0f, 0.0f		
			};

			objects->attachComponent(player, new Components::Shape(p_verts, 12));

			objects->attachComponent(player, new Components::Velocity(0.0f, 0.0f, 0.0f, 1000.0f, 2.0f, 400.0f));
			//objects->attachComponent(player, new Components::Collision(CollisionResponse::rigid_body));;
			objects->attachComponent(player, new Components::Texture("assets/ship.png"));
			objects->attachComponent(player, new Components::Health(100.0f));

			Entity* target = objects->pushEntity(new Entity(200.0f, 200.0f, 0.0f));
		
			objects->attachComponent(target, new Components::Shape(p_verts, 12));
		
			objects->attachComponent(target, new Components::Collision(CollisionResponse::static_body));
			objects->attachComponent(target, new Components::Health(100.0f));

			std::cout << glGetString(GL_VERSION) << "\n";

			Level::load("data/entities", objects);	
			run = true;
			return 0;
		}

		void Engine::initGL(int w, int h) {
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
			
						float p_verts[12];
						p_verts[0] = -16.0f;
						p_verts[1] = -16.0f;
						p_verts[2] = 0.0f;

						p_verts[3] = 16.0f;
						p_verts[4] = -16.0f;
						p_verts[5] = 0.0f;

						p_verts[6] = 16.0f;
						p_verts[7] = 16.0f;
						p_verts[8] = 0.0f;

						p_verts[9] = -16.0f;
						p_verts[10] = 16.0f;
						p_verts[11] = 0.0f;

						objects->attachComponent(t20, new Components::Shape(p_verts, 12));
					
						objects->attachComponent(t20, new Components::Collision(CollisionResponse::static_body));
						objects->attachComponent(t20, new Components::Health(100.0f));
						break;

					case SDLK_f:
						glm::vec3 rotation = glm::rotateZ(glm::vec3(1.0f, 0.0f, 0.0f), (float)(((Components::Shape*) player->components[Component::SHAPE])->rotation - PI/2.0f));
						glm::vec3 pos = player->pos + rotation*25.0f;

						Entity* projectile = objects->pushEntity(new Entity(pos));
							
						float t_verts[12];
						t_verts[0] = -16.0f;
						t_verts[1] = -16.0f;
						t_verts[2] = 0.0f;

						t_verts[3] = 16.0f;
						t_verts[4] = -16.0f;
						t_verts[5] = 0.0f;

						t_verts[6] = 16.0f;
						t_verts[7] = 16.0f;
						t_verts[8] = 0.0f;

						t_verts[9] = -16.0f;
						t_verts[10] = 16.0f;
						t_verts[11] = 0.0f;
					
						Components::Shape* p_shape = new Components::Shape(t_verts, 12);
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
		}

		void Engine::quit() {
			run = false;
		}

		bool Engine::isRunning() {
			return run;
		}
	}
}
