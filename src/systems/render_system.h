#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL_opengl.h>

#include <SDL2/SDL.h>

#include "core/entity.h"
#include "core/component.h"
#include "core/system.h"
#include "core/game_objects.h"

#include "components/shape.h"
#include "components/texture.h"

namespace JEngine {
	namespace Systems {
		class RenderSystem : public Core::System {
			public:
				RenderSystem(Core::GameObjects*, SDL_Window*);
				virtual ~RenderSystem();

				virtual void update(float);

				

			private:
				SDL_Window* window;

				float uv[8];
		};
	}
}

#endif
