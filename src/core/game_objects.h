// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: game_objects.h
// author: Jesper Stefansson
//
// Contains the GameObject class, which maintains a list of all
// entities and components in the engine. The class defines 
// functions for Entity and Component creation and deletion.

#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <list>

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Core {
		class GameObjects {

			public: 
				GameObjects();

				// Deallocates all components and enttities
				~GameObjects();
				
				// Pushes a new entity onto the entity list
				Entity* pushEntity(Entity*);

				// Attempts to attach a component to the given entity
				// 
				// return:
				// 		  0 - Component couldn't be attached
				// 		ptr - Pointer to Component if successful
				Component* attachComponent(Entity*, Component*);

				void trashEntity(Entity*);
				void processTrash();

				std::list<Component*> components[Component::NUM_TYPES];
				std::list<Entity*> entities;

			private:
				std::list<Entity*> trash;
		};
	}
}

#endif
