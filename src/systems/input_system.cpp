// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: input_system.cpp
// author: Jesper Stefansson

#include "input_system.h"

#include <typeinfo>
#include <string>
#include <iostream>
#include <cstring>

InputSystem::InputSystem(Engine* e, GameObjects* o) : 
	System(e, o) {}

InputSystem::~InputSystem() {}

void InputSystem::init() {
	key_binds["Space"] = "FIRE";
}

void InputSystem::update(float dt) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			engine->quit();

		if (e.type == SDL_KEYDOWN) {
			const char* key = SDL_GetKeyName(e.key.keysym.sym);

			if (
				key_binds.find(key) != key_binds.end() && 
				callbacks.find(key_binds[key]) != callbacks.end()
			) {
				
				const char* callback = key_binds[key];

				for (auto it = callbacks[callback].begin(); it != callbacks[callback].end(); it++)
					(*it)();
			}
		}
	}
}

void InputSystem::registerKeyEvent(const char* key, void (*callback)()) {
	callbacks[key].push_back(callback);	
}
