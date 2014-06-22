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
#include <cstring>

#include <SDL2/SDL.h>

#include "core/engine.h"
#include "core/system.h"
#include "core/game_objects.h"

struct CharCmp {
	bool operator()(char const* a, char const* b) {
		return (strcmp(a, b) < 0);
	}
};

enum KeyEventType {
	KEY_PRESSED = SDL_KEYDOWN,
	KEY_RELEASED = SDL_KEYUP
};

struct KeyEvent {
	const char* keyevent;
	int type;
	void (*callback)();

	KeyEvent(const char* event, int t, void (*fptr)()) {
		keyevent = event;
		type = t;
		callback = fptr;
	}

	KeyEvent() {
		keyevent = 0;
		type = 0;
		callback = 0;
	}
};

struct AxisEvent {
	const char* axisevent;
	void (*callback)(float);

	AxisEvent(const char* event, void (*fptr)(float)) {
		axisevent = event;
		callback = fptr;
	}

	AxisEvent() {
		axisevent = 0;
		callback = 0;
	}
};

struct KeyBind {
	const char* keyname;
	const char* keyevent;

	KeyBind(const char* name, const char* event) {
		keyname = name;
		keyevent = event;
	}

	KeyBind() {
		keyname = 0;
		keyevent = 0;
	}
};

struct AxisBind {
	const char* axisname;
	const char* axisevent;
	float scale;

	AxisBind(const char* name, const char* event, float s) {
		axisname = name;
		axisevent = event;
		scale = s;
	}

	AxisBind() {
		axisname = 0;
		axisevent = 0;
		scale = 0;
	}
};


// See file comments for class details
class InputSystem : public System {
	
	std::map<const char*, KeyEvent, CharCmp> key_callbacks;
	std::map<const char*, AxisEvent, CharCmp> axis_callbacks;
	
	std::map<const char*, KeyBind, CharCmp> key_binds;
	std::map<const char*, AxisBind, CharCmp> axis_binds;

	SDL_Event e;

public:
	InputSystem(Engine*, GameObjects*);
	virtual ~InputSystem();

	// Initialises the input bindings
	virtual void init();

	// Polls SDL for events and triggers the corresponding callback
	virtual void update(float dt);

	// Bind a keyboard event to a callback, parameters are:
	// 
	// const char* 		keyboard event, eg. "Fire"
	// int				key event type, eg. KEY_PRESSED or KEY_RELEASED
	// void (*)() 		function pointer to call upon keyevent occurance
	void bindAction(const char*, int, void (*)());

	// Bind an axis to a callback function, the axis can be
	// bound to keys and will then pass the maximum scale value
	// to the callback function. Parameters are:
	//
	// const char* 		axis event, eg. "MoveForward", or "MouseX"
	// void(*)(float)	function pointer to call upon axis event occurance.
	void bindAxis(const char*, void(*)(float));


};

#endif
