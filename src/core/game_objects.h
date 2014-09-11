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

		// Adds the entity to the trash list, making sure to only 
		// allow unique entities in the list.
		void trashEntity(Entity*);

		// Iterates through the trash list and deletes the entities
		void processTrash();
		
		// List of all attached components, grouped into the 
		// component ids for easy access
		std::list<Component*> components[EComponentType::NUM_TYPES];

		// List of all attached entities
		std::list<Entity*> entities;

	private:
		// The trash list, emptied upon calling GameObjects::processTrash
		std::list<Entity*> trash;
};

#endif
