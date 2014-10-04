#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#ifndef MAX_ENTITY
#define MAX_ENTITY (250)
#endif

#ifndef MAX_COMPONENT 
#define MAX_COMPONENT (250)
#endif

#include <glm/glm.hpp>

#include "core/globals.h"

#include "ecs/components.hpp"
#include "ecs/component_manager.h"

struct Entity {
	unsigned int id = 0;
};

class EntityManager {
	unsigned int next = 0;
	Entity data[MAX_ENTITY];

public:
	Entity* createEntity();
	void removeEntity(Entity*);
};

extern EntityManager entities;

#endif
