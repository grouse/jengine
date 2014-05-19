#ifndef SHAPE_H
#define SHAPE_H

#include <initializer_list>
#include <vector>

#include <SDL2/SDL_opengl.h>

#include "core/component.h"
#include "core/entity.h"

namespace JEngine {
	namespace Components {
		class Shape : public Core::Component {
			public:
				Shape(std::initializer_list<GLfloat>);
				virtual ~Shape();

				virtual bool canAttach(Core::Entity&);

				void rotate(double);
				void setRotation(double);

				std::vector<GLfloat> vertices;

				float rotation;

				GLuint vbo;
		};
	}
}

#endif
