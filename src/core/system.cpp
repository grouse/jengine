// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "system.h"

#include <iostream>

namespace JEngine {
	namespace Core {
		System::System(GameObjects* objects) {
			this->objects = objects;
		}

		System::~System() {}
	}
}
