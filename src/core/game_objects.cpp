// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: game_objects.cpp
// author: Jesper Stefansson

#include <iostream>

#include "game_objects.h"

namespace JEngine {
	namespace Core {
		GameObjects::GameObjects() {}
		
		GameObjects::~GameObjects() {
			// Deallocate components
			for (unsigned int i = 0; i < Component::NUM_TYPES; i++)
				for (auto it  = components[i].begin(); it != components[i].end(); it++) 
					delete (*it);

			// Deallocate entities
			for (auto it = entities.begin(); it != entities.end(); it++)
				delete (*it);	
		}

		void GameObjects::trashEntity(Entity* e) {
			trash.push_back(e); // Add to trash
			trash.unique();		// Ensure only unique entities
		}

		Entity* GameObjects::pushEntity(Entity* e) {
			entities.push_back(e); 
			return e;
		}

		Component* GameObjects::attachComponent(Entity* e, Component* c) {
			// Returns false if the entity does not meet the component's dependencies
			if (!c->canAttach(*e)) {
				std::cout << "Failed to attach component: " << c->type << " to entity: " << e << "\n";
				return 0;
			}

			components[c->type].push_back(c); 	// add to component list
			e->attach(c->type, c);				// attach to entity
			c->owner = e;						// set owner of component

			return c;
		}

		void GameObjects::processTrash() { 
			// Iterate over all entities in te trash list
			for (auto it = trash.begin(); it != trash.end(); it++) {
				Entity* e = (*it);
				
				// Iterate over all components of entity and delete them
				for (unsigned int i = 0; i < Component::NUM_TYPES; i++) {
					if (e->components[i] != 0) {
						components[i].remove(e->components[i]);
					
						delete e->components[i];
						e->components[i] = 0;
					}
				}

				entities.remove(e); // Remove from entity list
				delete e;
				e = 0;

				it = trash.erase(it); // Finally, remove from trash
			}
		}
	}
}
