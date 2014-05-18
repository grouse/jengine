#include "system.h"

#include <iostream>

namespace JEngine {

	System::System(GameObjects* objects) {
		this->objects = objects;
	}

	System::~System() {}


	void System::update(float dt) {
		objects->processTrash();
	}
}
