// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include <SDL2/SDL.h>

#include "core/engine.h"

#include "systems/collision_system.h"
#include "systems/health_system.h"
#include "systems/life_time_system.h"
#include "systems/movement_system.h"
#include "systems/render_system.h"
#include "systems/audio_system.h"

int main(int argc, char* argv[]) {
	JEngine::Core::GameObjects objects;
	JEngine::Core::Engine engine(&objects);

	engine.attachSystem(new JEngine::Systems::LifeTimeSystem(&objects));
	engine.attachSystem(new JEngine::Systems::MovementSystem(&objects));
	engine.attachSystem(new JEngine::Systems::CollisionSystem(&objects));
	engine.attachSystem(new JEngine::Systems::HealthSystem(&objects));
	engine.attachSystem(new JEngine::Systems::RenderSystem(&objects));
	engine.attachSystem(new JEngine::Systems::AudioSystem(&objects));

	if (engine.init() != 0)
		return -1;

	Uint32 old_time, current_time;
	current_time = SDL_GetTicks();

	float dt;

	while (engine.isRunning()) {
		old_time = current_time;
		current_time = SDL_GetTicks();
		dt = (current_time - old_time) / 1000.0f;

		SDL_Event e;
		while (SDL_PollEvent(&e))
			engine.handleInput(e);

		engine.update(dt);		
	}
	
	return 0;
}
