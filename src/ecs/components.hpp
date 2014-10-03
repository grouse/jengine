#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>

struct Mesh {
	unsigned int vertices_size;
	glm::vec3* vertices;

	Mesh() {
		vertices = NULL;
	};

	Mesh(unsigned int size) {
		vertices_size = size;
		vertices = new glm::vec3[size];
	};

	~Mesh() {
	   	if (vertices != NULL)	
			delete [] vertices;
	};
};

struct Collision {
	bool allow_overlap = false; 	// determines whether other objects can overlap this one
	Mesh bounding_box;				// bounding box, keep axis aligned until collision then rotate

	Collision() {};

	Collision(unsigned int vertices) : 
		bounding_box(vertices) {};
};

struct Movement {
	glm::vec3 velocity = glm::vec3(0.0f);
	float max_velocity = 100.0f; 
};

struct PhysicsBody {
	float friction = 0.0f; 			// =0: constant, >0: factor of velocity lost
	float bounce = 1.0f;			// <1: -accelerate, =1: constant, >1: accelerate
};

struct Texture {
	unsigned int texture_id;		// Texture id as represented in RenderSystem
	unsigned int width, height;		// Texture dimensions
	int components;					// Pixel components, eg. RGBA
};


#endif
