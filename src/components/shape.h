// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: shape.h
// author: Jesper Stefansson
//
// Contains the Shape component, which is used as the mesh
// for the entity it is attached to. 

#ifndef SHAPE_H
#define SHAPE_H

#include <initializer_list>
#include <vector>

#include <SDL2/SDL_opengl.h>

#include "core/component.h"
#include "core/entity.h"

// See fire comments for class details
class Shape : public Component {
	public:
		Shape(std::initializer_list<float>); 	// vectors initialised by initializer_list
		Shape(float*, unsigned int);			// params: float array, array length

		virtual ~Shape();

		// Returns true, Shape currently does not
		// depend on any other component
		virtual bool canAttach(Entity&);

		// Rotates the shape by param radians 
		void rotate(double);

		// Resets the shape's rotation to 0, then rotates
		// it by param radians
		void setRotation(double);

		float rotation;					// current rotation of shape
		std::vector<float> vertices;	// the vertices of the shape
};

#endif
