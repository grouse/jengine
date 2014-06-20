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
	KEY_PRESSED = 0,
	KEY_RELEASED = 1
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

struct KeyBind {
	const char* keyname;
	char keycode;
	const char* keyevent;

	KeyBind(const char* name, char code, const char* event) {
		keyname = name;
		keycode = code;
		keyevent = event;
	}

	KeyBind() {
		keyname = 0;
		keycode = 0;
		keyevent = 0;
	}
};

// See file comments for class details
class InputSystem : public System {
	
	std::map<const char*, KeyEvent, CharCmp> p_callbacks;
	std::map<const char*, KeyEvent, CharCmp> r_callbacks;
	std::map<const char*, KeyBind, CharCmp> key_binds;

	SDL_Event e;

public:
	InputSystem(Engine*, GameObjects*);
	virtual ~InputSystem();

	// Initialises the input bindings
	virtual void init();

	// Polls SDL for events and triggers the corresponding callback
	virtual void update(float dt);

	void registerKeyEvent(const char*, int, void (*)());


};

#endif
