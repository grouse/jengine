#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <initializer_list>

#include <glm/glm.hpp>

#include <iostream>

struct Mesh {
	std::vector<float> vertices;;

	Mesh() {};
	Mesh(float* verts, unsigned int n) : vertices(verts, verts+n) {};
};

struct Collision {
	bool allow_overlap = false; 	// determines whether other objects can overlap this one
	Mesh bounding_box;				// bounding box, keep axis aligned until collision then rotate

	Collision() {};
	
	Collision(Mesh m) {
		bounding_box = m;
	};
};

struct Movement {
	glm::vec3 velocity = glm::vec3(0.0f);
	float max_velocity = 100.0f; 
};

struct PhysicsBody {
	bool gravity = true;
	float friction = 0.0f; 			// =0: constant, >0: factor of velocity lost
	float bounce = 1.0f;			// <1: -accelerate, =1: constant, >1: accelerate
};

struct Texture {
	unsigned int texture_id;		// Texture id as represented in RenderSystem
	unsigned int width, height;		// Texture dimensions
	int components;					// Pixel components, eg. RGBA
};

struct Position {
	float x, y, z;
};

#endif
