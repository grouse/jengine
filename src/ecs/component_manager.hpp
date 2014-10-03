#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#ifndef MAX_ENTITY
#define MAX_ENTITY (250)
#endif

#ifndef MAX_COMPONENT
#define MAX_COMPONENT (250)
#endif

template <typename T>
class ComponentManager {
	unsigned int next = 0;
	T components[MAX_COMPONENT];

	unsigned int ent_cmp_id[MAX_ENTITY];
	unsigned int cmp_ent_id[MAX_COMPONENT];

public:
	void attachTo(unsigned int ent, T cmp) {
		components[next] = cmp;
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
		
		components[cmp_dst] = components[cmp_src];
		ent_cmp_id[ent_dst] = ent_cmp_id[ent_src];	
		cmp_ent_id[cmp_dst] = cmp_ent_id[cmp_src];	
		
		next--;
	};

	T* getCmpFrom(unsigned int ent) { 
		return &components[ent_cmp_id[ent]];
	};


};

#endif
