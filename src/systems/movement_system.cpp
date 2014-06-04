#include "movement_system.h"

namespace JEngine {
	namespace Systems {
		MovementSystem::MovementSystem(Core::GameObjects* objects) : Core::System(objects) {}
		MovementSystem::~MovementSystem() {}

		void MovementSystem::init() {
			initialised = true;
		}

		void MovementSystem::update(float dt) {
			for (auto it = objects->components[Core::Component::VELOCITY].begin(); it != objects->components[Core::Component::VELOCITY].end(); it++) {

				Components::Velocity* v = (Components::Velocity*) (*it);
				Core::Entity* e = v->owner;;

				e->pos += v->vec3 * dt;
			}
		}
	}
}
