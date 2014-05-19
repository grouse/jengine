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
