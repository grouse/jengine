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
	key_binds["Space"] = KeyBind("Space", "Fire");
	
	axis_binds["W"] = AxisBind("W", "MoveForward", -1.0f);
	axis_binds["S"] = AxisBind("S", "MoveForward", 1.0f);

	axis_binds["A"] = AxisBind("A", "MoveRight", -1.0f);
	axis_binds["D"] = AxisBind("D", "MoveRight", 1.0f);
}

void InputSystem::update(float dt) {
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			engine->quit();

		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			const char* key = SDL_GetKeyName(e.key.keysym.sym);

			if (key_binds.find(key) != key_binds.end()) {
				KeyBind kbind = key_binds[key];
				KeyEvent kevent = key_callbacks[kbind.keyevent];

				if (kevent.callback != 0 && kevent.type == e.type)
					kevent.callback();
			}

			if (axis_binds.find(key) != axis_binds.end()) {
				AxisBind abind = axis_binds[key];
				AxisEvent aevent = axis_callbacks[abind.axisevent];

				if (aevent.callback != 0)
					aevent.callback(abind.scale);
			}
		}
	}
}

void InputSystem::bindAction(const char* key, int t, void (*callback)()) {
	key_callbacks[key] = KeyEvent(key, t, callback);
}

void InputSystem::bindAxis(const char* axis, void (*callback)(float)) {
	axis_callbacks[axis] = AxisEvent(axis, callback);
}
