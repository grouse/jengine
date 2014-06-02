#include "life_time_system.h"

namespace JEngine {
	namespace Systems {

		LifeTimeSystem::LifeTimeSystem(Core::GameObjects* objects) : Core::System(objects) {}
		LifeTimeSystem::~LifeTimeSystem() {}

		void LifeTimeSystem::update(float dt) {
			for (auto it = objects->components[Core::Component::LIFETIME].begin(); it != objects->components[Core::Component::LIFETIME].end(); it++) {
				Components::LifeTime* c = (Components::LifeTime*) (*it);

				c->remaining -= dt;
				if (c->remaining <= 0)
					objects->trashEntity(c->owner);
			}
			
		}
	}
}
