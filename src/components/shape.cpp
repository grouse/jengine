// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: shape.cpp
// author: Jesper Stefansson

#include "shape.h"

#include <math.h>
#include <iostream>

Shape::Shape(std::initializer_list<float> v) :
   	Component(EComponentType::SHAPE),	
	vertices(v)	{

	rotation = 0;
}

Shape::Shape(float* v, unsigned int size) :
   	Component(EComponentType::SHAPE),	
	vertices(v, v + size) {

		rotation = 0;
	}

Shape::~Shape() {}

// Rotate the shape by radians
// TODO: Switch out logic in favour of GLM
void Shape::rotate(double angle) {
	double s = sin(angle); // compute sin once
	double c = cos(angle); // compute cos once

	double xt, yt; // vector coordinate
	double xr, yr; // rotated coordinates

	xt = vertices[0];
	yt = vertices[1];

	xr = xt * c - yt * s; 
	yr = xt * s + yt * c;

	vertices[0] = xr;
	vertices[1] = yr;

	
	xt = vertices[3];
	yt = vertices[4];

	xr = xt * c - yt * s;
	yr = xt * s + yt * c;

	vertices[3] = xr;
	vertices[4] = yr;

	xt = vertices[6];
	yt = vertices[7];

	xr = xt * c - yt * s;
	yr = xt * s + yt * c;

	vertices[6] = xr;
	vertices[7] = yr;

	xt = vertices[9];
	yt = vertices[10];

	xr = xt * c - yt * s;
	yr = xt * s + yt * c;

	vertices[9] = xr;
	vertices[10] = yr;

	rotation += angle;
	if (rotation >= 6.28318531 || rotation <= -6.28318531)
		rotation = 0;
}

void Shape::setRotation(double angle) {
	if (rotation != 0)
		rotate(-rotation);

	rotate(angle);
}
