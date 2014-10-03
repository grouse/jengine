#include "entity_manager.h"

Entity* EntityManager::createEntity() {
	entities[next].id = next;
	return &entities[next++];
};

void EntityManager::removeEntity(Entity* e) {
	unsigned int id = e->id;
	e = NULL;

	components.mesh.removeFrom(id);
	components.collision.removeFrom(id);
	components.movement.removeFrom(id);
	components.physics_body.removeFrom(id);
	components.texture.removeFrom(id);

	next--;
	if (e->id == next)
		return;

	entities[id].id = entities[next].id;
};
