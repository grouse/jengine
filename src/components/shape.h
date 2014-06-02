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
				Shape(std::initializer_list<float>);
				Shape(float*, unsigned int);

				virtual ~Shape();

				virtual bool canAttach(Core::Entity&);

				void rotate(double);
				void setRotation(double);

				std::vector<float> vertices;

				float rotation;

				GLuint vbo;
		};
	}
}

#endif
