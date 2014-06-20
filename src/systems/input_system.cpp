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
	key_binds["Space"] = KeyBind("Space", SDLK_SPACE, "FIRE");
}

void InputSystem::update(float dt) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			engine->quit();

		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			const char* key = SDL_GetKeyName(e.key.keysym.sym);

			if (key_binds.find(key) != key_binds.end()) {
				KeyBind bind = key_binds[key];

				KeyEvent event = (e.type == SDL_KEYDOWN) ? 
					p_callbacks[bind.keyevent] : 
					r_callbacks[bind.keyevent];

				if (event.callback != 0)
					event.callback();

			}
		}
	}
}

void InputSystem::registerKeyEvent(const char* key, int t, void (*callback)()) {
	if (t == KEY_PRESSED) {
		p_callbacks[key] = KeyEvent(key, t, callback);
	} else {
		r_callbacks[key] = KeyEvent(key, t, callback);
	}
}
