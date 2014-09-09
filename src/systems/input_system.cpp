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
	SDL_SetRelativeMouseMode(SDL_TRUE);

	key_binds["P"] = KeyBind("P", "Reset");
	
	
	key_binds["Space"] = KeyBind("Space", "Jump");
	key_binds["F"] = KeyBind("F", "Fire");
	
	axis_binds["W"] = AxisBind("W", "MoveForward", -1.0f);
	axis_binds["S"] = AxisBind("S", "MoveForward", 1.0f);

	axis_binds["A"] = AxisBind("A", "MoveRight", -1.0f);
	axis_binds["D"] = AxisBind("D", "MoveRight", 1.0f);

	axis_binds["Q"] = AxisBind("Q", "Turn", -1.0f);
	axis_binds["E"] = AxisBind("E", "Turn", 1.0f);
	
	axis_binds["Left"] = AxisBind("Left", "Turn", -1.0f);
	axis_binds["Right"] = AxisBind("Right", "Turn", 1.0f);

	axis_binds["MouseX"] = AxisBind("MouseX", "TurnAt", 1.0f);

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
				
				float value = (e.type == KEY_PRESSED) ? abind.scale : 0;
				if (aevent.callback != 0) 
					aevent.callback(value);
			}
		}

		if (e.type == SDL_MOUSEMOTION) {
			if (axis_binds.find("MouseX") != axis_binds.end()) {
				AxisBind abind = axis_binds["MouseX"];
				AxisEvent aevent = axis_callbacks[abind.axisevent];

				if (aevent.callback != 0)
					aevent.callback((float)e.motion.xrel*abind.scale);
			}
			
			if (axis_binds.find("MouseY") != axis_binds.end()) {
				AxisBind abind = axis_binds["MouseY"];
				AxisEvent aevent = axis_callbacks[abind.axisevent];

				if (aevent.callback != 0)
					aevent.callback((float)e.motion.yrel*abind.scale);
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
