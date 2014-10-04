#include "entity_manager.h"

EntityManager entities;

Entity* EntityManager::createEntity() {
	data[next].id = next;
	return &data[next++];
};

void EntityManager::removeEntity(Entity* e) {
	unsigned int id = e->id;
	e = NULL;

	components.mesh.removeFrom(id);
	components.collision.removeFrom(id);
	components.movement.removeFrom(id);
	components.physics_body.removeFrom(id);
	components.texture.removeFrom(id);
	components.position.removeFrom(id);

	next--;
	if (e->id == next)
		return;

	data[id].id = data[next].id;
};
