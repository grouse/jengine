#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <list>
#include <vector>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"
#include "core/level.h"

#include "systems/movement_system.h"
#include "systems/collision_system.h"
#include "systems/render_system.h"
#include "systems/life_time_system.h"
#include "systems/health_system.h"

#include "components/shape.h"
#include "components/velocity.h"
#include "components/collision.h"
#include "components/life_time.h"
#include "components/texture.h"
#include "components/health.h"
#include "components/damage.h"


namespace JEngine {
	namespace Core {
		class Engine {
			public:
				Engine();
				virtual ~Engine();

				int init(const char*, int, int);

				void handleInput(SDL_Event&);
				void update(float);

				void quit();
				bool isRunning();

				void deleteEntity(Entity*);

			private:
				SDL_Window* window;
				SDL_GLContext glcontext;

				bool run;

				void initGL(int, int);

				GameObjects* objects;
				System* system;
				std::list<System*> systems;

				Entity* player;
				
				bool input_w = false, input_s = false, input_a = false, input_d = false;



		};
	}
}

#endif
