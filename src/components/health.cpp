// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "health.h"


namespace JEngine {
	namespace Components {
		Health::Health(float hp) : Core::Component(Core::Component::HEALTH) {
			this->health = hp;
		}

		Health::~Health() {}

		bool Health::canAttach(Core::Entity& e) {
			return true;
		}
	}
}
