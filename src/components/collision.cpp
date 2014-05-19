#include "collision.h"

#include <iostream>

namespace JEngine {
	namespace Components {
		Collision::Collision(void (*response)(Core::Entity*, Core::Entity*, glm::vec3, Core::GameObjects*)) : Core::Component(Core::Component::COLLISION)	{
			this->response = response;
		}

		Collision::~Collision() {}

		bool Collision::canAttach(Core::Entity& e) {
			return true;
		}
	}


	namespace CollisionResponse {
		void rigid_body(Core::Entity* e1, Core::Entity* e2, glm::vec3 overlap, Core::GameObjects* objects) {
			e1->pos -= overlap;
			
			Components::Velocity* v = (Components::Velocity*) e1->components[Core::Component::VELOCITY];
			v->vec3 = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		
		void static_body(Core::Entity* e1, Core::Entity* e2, glm::vec3 overlap, Core::GameObjects* objects) {}

		void projectile(Core::Entity* e1, Core::Entity* e2, glm::vec3 overlap, Core::GameObjects* objects) {
			if (e1->components[Core::Component::DAMAGE] != 0 && e2->components[Core::Component::HEALTH] != 0) {
				Components::Damage* d = (Components::Damage*) e1->components[Core::Component::DAMAGE];
				Components::Health* h = (Components::Health*) e2->components[Core::Component::HEALTH];

				h->health -= d->damage;
				std::cout << "DAMAGE! " << d->damage << "\nRemaining health: " << h->health << "\n";
			}

			objects->trashEntity(e1);
		}
	}
}
