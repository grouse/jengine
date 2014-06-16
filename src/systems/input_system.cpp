// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: input_system.cpp
// author: Jesper Stefansson

#include "input_system.h"

namespace JEngine {
	namespace Systems {
	
		InputSystem::InputSystem(Core::Engine* e, Core::GameObjects* o) : 
			Core::System(e, o) {}

		InputSystem::~InputSystem() {}

		void InputSystem::init() {
			key_binds["Space"] = "FIRE";

		}

		void InputSystem::update(float dt) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					engine->quit();
				}

				if (e.type == SDL_KEYDOWN) {
					const char* key = SDL_GetKeyName(e.key.keysym.sym);
					const char* input = key_binds[key];


					for (auto it = callbacks[input].begin(); it != callbacks[input].end(); it++)
					   (*it)();	
				}
			}
		}

		void InputSystem::registerKeyEvent(const char* key, void (*callback)()) {
			callbacks[key].push_back(callback);	
		}
	}
}
