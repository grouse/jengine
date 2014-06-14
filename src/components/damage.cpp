// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: damage.cpp
// author: Jesper Stefansson

#include "damage.h"

namespace JEngine {
	namespace Components {	
		Damage::Damage(float dmg) : Core::Component(Core::Component::DAMAGE) {
			this->damage = dmg;
		}

		Damage::~Damage() {}

		bool Damage::canAttach(Core::Entity& e) {
			return true;
		}

	}
}
