#include "system.h"

#include <iostream>

namespace JEngine {
	namespace Core {
		System::System(GameObjects* objects) {
			this->objects = objects;
		}

		System::~System() {}


		void System::update(float dt) {
			objects->processTrash();
		}
	}
}
