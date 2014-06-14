// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: life_time.cpp
// author: Jesper Stefansson

#include "life_time.h"

namespace JEngine {
	namespace Components {
		LifeTime::LifeTime(float t) : Core::Component(Core::Component::LIFETIME) {
			remaining = t;
		}

		LifeTime::~LifeTime() {}

		bool LifeTime::canAttach(Core::Entity& e) {
			return true;
		}	
	}
}
