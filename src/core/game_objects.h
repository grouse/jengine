#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <list>

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	class GameObjects {

		public: 
			GameObjects();
			~GameObjects();

			std::list<Component*> components[Component::NUM_TYPES];
			std::list<Entity*> entities;

			Entity* pushEntity(Entity*);
			Component* attachComponent(Entity*, Component*);

			void trashEntity(Entity*);
			void processTrash();

		private:
			std::list<Entity*> trash;
	};
}

#endif
