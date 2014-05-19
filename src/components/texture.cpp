#include "texture.h"

#include <iostream>

namespace JEngine {
	namespace Components {	
		Texture::Texture(const char* filename) : Core::Component(Core::Component::TEXTURE) {
			this->filename = filename;

			unsigned char* pixels = stbi_load(filename, &width, &height, &components, 0);

			glGenTextures(1, &GLtex);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GLtex);

			if (components == 4 ) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			} else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			stbi_image_free(pixels);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::~Texture() {
			glDeleteTextures(1, &GLtex);
		}

		bool Texture::canAttach(Core::Entity& e) {
			return true;
		}
	}
}
