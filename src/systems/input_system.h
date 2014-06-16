// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: input_system.h
// author: Jesper Stefansson
//
// Contains the InputSystem which polls for input events from
// SDL and triggers the corresponding callback function

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <map>
#include <list>

#include <SDL2/SDL.h>

#include "core/engine.h"
#include "core/system.h"
#include "core/game_objects.h"

namespace JEngine {
	namespace Systems {

		// See file comments for class details
		class InputSystem : public Core::System {
			
			// Index is input event (eg. JUMP), value is the function to call when triggered
			std::map<const char*, std::list<void (*)()>> callbacks;

			// Index is the keycode (eg. SPACE), value is the input event (eg. JUMP)
			std::map<const char*, const char*> key_binds;

			SDL_Event e;

		public:
			InputSystem(Core::Engine*, Core::GameObjects*);
			virtual ~InputSystem();

			// Initialises the input bindings
			virtual void init();

			// Polls SDL for events and triggers the corresponding callback
			virtual void update(float dt);

			void registerKeyEvent(const char*, void (*)());


		};
	}
}

#endif
