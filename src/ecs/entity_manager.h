#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#ifndef MAX_ENTITY
#define MAX_ENTITY (250)
#endif

#ifndef MAX_COMPONENT 
#define MAX_COMPONENT (250)
#endif

#include "ecs/components.hpp"
#include "ecs/component_manager.hpp"

struct Entity {
	unsigned int id = 0;
};


struct ComponentManagers { 
	ComponentManager<Mesh> mesh;
	ComponentManager<Collision> collision;
	ComponentManager<Movement> movement;
	ComponentManager<PhysicsBody> physics_body;
	ComponentManager<Texture> texture;
};

class EntityManager {
	unsigned int next = 0;
	Entity entities[MAX_ENTITY];

public:
	ComponentManagers components;

	Entity* createEntity();
	void removeEntity(Entity*);
};

#endif
