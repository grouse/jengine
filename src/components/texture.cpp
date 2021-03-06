// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: texture.cpp
// author: Jesper Stefansson

#include "texture.h"

#include <iostream>

Texture::Texture(const char* filename, std::initializer_list<float> texcoords) : 
   	Component(EComponentType::TEXTURE),	
	uv(texcoords) {
	
	// Load pixeldata, width, height, and components from file
	unsigned char* pixels = stbi_load(filename, &width, &height, &components, 0);

	// Allocate a new texture in OpenGL
	glGenTextures(1, &GLtex);

	glActiveTexture(GL_TEXTURE0);
	
	// Set active texture id
	glBindTexture(GL_TEXTURE_2D, GLtex);


	if (components == 4 ) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// cleanup
	stbi_image_free(pixels);

	// unbind texture for cleanliness
	glBindTexture(GL_TEXTURE_2D, 0);

	for (int i = 0; i < uv.size(); i++) {
		uv[i] = uv[i] / width;
		uv[i+1] = uv[i+1] / height;
		i++;
	}
}

Texture::Texture(const char* filename, float* texcoords, unsigned int n) :
   	Component(EComponentType::TEXTURE),	
	uv(texcoords, texcoords + n) {
	
	// Load pixeldata, width, height, and components from file
	unsigned char* pixels = stbi_load(filename, &width, &height, &components, 0);

	// Allocate a new texture in OpenGL
	glGenTextures(1, &GLtex);

	glActiveTexture(GL_TEXTURE0);
	
	// Set active texture id
	glBindTexture(GL_TEXTURE_2D, GLtex);


	if (components == 4 ) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// cleanup
	stbi_image_free(pixels);

	// unbind texture for cleanliness
	glBindTexture(GL_TEXTURE_2D, 0);

	for (int i = 0; i < uv.size(); i++) {
		uv[i] = uv[i] / width;
		uv[i+1] = uv[i+1] / height;
		i++;
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &GLtex);
}
