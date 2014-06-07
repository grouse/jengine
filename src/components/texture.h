// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image.h>
#include <SDL2/SDL_opengl.h>

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {
		class Texture : public Core::Component {
			public:
				Texture(const char*);
				virtual ~Texture();

				virtual bool canAttach(Core::Entity&);

				const char* filename;
				GLuint GLtex;
				int width, height;
				int components;

				GLuint vbo, ibo;


		};
	}
}

#endif
