// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

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
