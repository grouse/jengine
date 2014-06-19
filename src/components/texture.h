// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: texture.h
// author: Jesper Stefansson
//
// Contains the Texture component, which handles all the 
// necessary logic to load a texture from file and load
// it into GPU memory using OpenGL

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image.h>
#include <SDL2/SDL_opengl.h>

#include "core/entity.h"
#include "core/component.h"

// See file comments for class details
class Texture : public Component {
	public:
		// Load texture from paramter file name
		Texture(const char*);
		virtual ~Texture();

		// Returns true if Entity has a shape 
		// component attached to it.
		virtual bool canAttach(Entity&);

		const char* filename;	// Texture file
		GLuint GLtex;			// Texture OpenGL id
		int width, height;		// Texture dimensions
		int components;			// Texture components (eg. RGBA)
};

#endif
