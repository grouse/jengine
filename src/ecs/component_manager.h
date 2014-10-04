#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#ifndef MAX_ENTITY
#define MAX_ENTITY (250)
#endif

#ifndef MAX_COMPONENT
#define MAX_COMPONENT (250)
#endif

#include "ecs/components.hpp"

template <typename T>
class ComponentManager {
public:
	unsigned int next = 0;
	T data[MAX_COMPONENT];

	unsigned int ent_cmp_id[MAX_ENTITY];
	unsigned int cmp_ent_id[MAX_COMPONENT];

	void attachTo(unsigned int ent, T cmp) {
		data[next] = cmp;
		ent_cmp_id[ent] = next;
		cmp_ent_id[next] = ent;
		next++;	
	};

	void removeFrom(unsigned int ent) { 
		if (ent == next-1) {
			next--;
			return;
		}

		unsigned int cmp_src = next-1;
		unsigned int ent_src = cmp_ent_id[cmp_src];

		unsigned int cmp_dst = ent_cmp_id[ent];
		unsigned int ent_dst = cmp_ent_id[cmp_dst];
		
		data[cmp_dst] = data[cmp_src];
		ent_cmp_id[ent_dst] = ent_cmp_id[ent_src];	
		cmp_ent_id[cmp_dst] = cmp_ent_id[cmp_src];	
		
		next--;
	};

	T* getCmpFrom(unsigned int ent) { 
		return &data[ent_cmp_id[ent]];
	};

	T& operator [] (unsigned int i) {
		return data[i];
	};
};

struct ComponentManagers {
	ComponentManager<Mesh> mesh;
	ComponentManager<Collision> collision;
	ComponentManager<Movement> movement;
	ComponentManager<PhysicsBody> physics_body;
	ComponentManager<Texture> texture;
	ComponentManager<Position> position;
};

extern ComponentManagers components;

#endif
