// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: collision_system.cpp
// author: Jesper Stefansson

#include "collision_system.h"

#include <iostream>

CollisionSystem::CollisionSystem(Engine* e, GameObjects* o) : 
	System(e, o) {}

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::init() {
	initialised = true;
}

void CollisionSystem::update(float dt) {

	for (auto it = objects->components[EComponentType::COLLISION].begin(); it != objects->components[EComponentType::COLLISION].end(); it++) {
		auto jt = it;
		
		for (jt++; jt != objects->components[EComponentType::COLLISION].end(); jt++) {
			Collision* c1 = (Collision*) (*it);
			Collision* c2 = (Collision*) (*jt);

			Entity* e1 = c1->owner;
			Entity* e2 = c2->owner;

			Shape* s1 = (Shape*) (e1->components[EComponentType::SHAPE]);
			Shape* s2 = (Shape*) (e2->components[EComponentType::SHAPE]);
			
			// Transform s1 vectors to e1 position and save them in an array of glm::vec3
			glm::vec3 a[4];
			a[0] = glm::vec3(s1->vertices[0], s1->vertices[1], 0.0f) + e1->pos;		// upper-left corner
			a[1] = glm::vec3(s1->vertices[3], s1->vertices[4], 0.0f) + e1->pos;		// upper-right corner
			a[2] = glm::vec3(s1->vertices[6], s1->vertices[7], 0.0f) + e1->pos;		// bottom-right corner
			a[3] = glm::vec3(s1->vertices[9], s1->vertices[10], 0.0f) + e1->pos;	// bottom-left corner

			// Transform s2 vectors to e2 position and save them in an array of glm::vec3
			glm::vec3 b[4];
			b[0] = glm::vec3(s2->vertices[0], s2->vertices[1], 0.0f) + e2->pos;		// upper-left corner
			b[1] = glm::vec3(s2->vertices[3], s2->vertices[4], 0.0f) + e2->pos;		// upper-right corner
			b[2] = glm::vec3(s2->vertices[6], s2->vertices[7], 0.0f) + e2->pos;		// bottom-right corner
			b[3] = glm::vec3(s2->vertices[9], s2->vertices[10], 0.0f) + e2->pos;	// bottom-left corner

			// Calculate 4 axes from the shape vectors, only 2 axes per shape is used
			// as the engine currently only fully supports squares
			glm::vec3 axes[8];
			axes[0] = glm::normalize(a[0] - a[1]);
			axes[1] = glm::normalize(a[1] - a[2]);
			axes[2] = glm::normalize(a[2] - a[3]);
			axes[3] = glm::normalize(a[3] - a[0]);
			
			axes[4] = glm::normalize(b[0] - b[1]);
			axes[5] = glm::normalize(b[1] - b[2]);
			axes[6] = glm::normalize(b[2] - b[3]);
			axes[7] = glm::normalize(b[3] - b[0]);

			bool collision = true;

			float overlapScalar = 1000.0f; 
			glm::vec3 overlapVec = glm::vec3(0.0f);

			for (unsigned int i = 0; i < 8 && collision; i++) {
				// Get the normal of the axis
				glm::vec3 axis = axes[i];

				// Project the shape vectors onto the axis, project only returns the
				// min and max values of these projections as the final projection
				glm::vec3 a_projection = project(a, axis);
				glm::vec3 b_projection = project(b, axis);

				// If the projections overlap, there is a collision on 1 axis. All 4
				// axis must have an overlap to be a full collision
				collision = overlaps(a_projection, b_projection);
				if (collision) {
					float o = getOverlap(a_projection, b_projection);

					// Save the smallest overlap so that we move the entities
					// the shortest distance possible to no longer have collision
					if (o < overlapScalar) {
						overlapScalar = o;
						overlapVec = axis;
					}
				}	
			}

			// If a collision is detected, we call the attached collision response function
			if (collision) {
				glm::vec3 direction = glm::normalize(e1->pos - e2->pos);
				glm::vec3 displacement = overlapScalar*overlapVec;

				if (glm::dot(direction, overlapVec) < 0.0f) {
					c1->response(e1, e2, -displacement, objects);
					c2->response(e2, e1, displacement, objects);
				} else {
					c1->response(e1, e2, displacement, objects);
					c2->response(e2, e1, -displacement, objects);
				}
			}
		}
	}
}

glm::vec3 CollisionSystem::project(glm::vec3* shape, glm::vec3 axis) {
	// We're only interested in the minimum and maximum dot-products
	// between the shape vectors and the axis
	float min = glm::dot(axis, shape[0]);
	float max = min;

	for (unsigned int i = 0; i < 4; i++) {
		float tmp = glm::dot(axis, shape[i]);

		if (tmp < min) {
			min = tmp;
		} 
		
		if (tmp > max) {
			max = tmp;
		}
	}

	return glm::vec3(min, max, 0.0f);
}

bool CollisionSystem::overlaps(glm::vec3 a, glm::vec3 b) {
	if (contains(a.x, b)) return true;
	if (contains(a.y, b)) return true;
	if (contains(b.x, a)) return true;
	if (contains(b.y, a)) return true;

	return false;
}

float CollisionSystem::getOverlap(glm::vec3 a, glm::vec3 b) {
	float x = (a.x >= b.x) ? a.x : b.x;
	float y = (a.y <= b.y) ? a.y : b.y;
	float max = (x >= y) ? x : y;
	float min = (x >= y) ? y : x;

	return max-min;
}

bool CollisionSystem::contains(float n, glm::vec3 r) {
	float a = r.x, b = r.y;
	if (b < a) {
		a = b;
		b = r.x;
	}

	return (n > a && n < b);
}

glm::vec3 CollisionSystem::perp(glm::vec3 v) {
	return glm::vec3(v.y, -v.x, 0.0f);
}
