// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "core/system.h"
#include "core/game_objects.h"

namespace JEngine {
	namespace Systems {
		class AudioSystem : public Core::System {
			public:
				AudioSystem(Core::GameObjects*);
				virtual ~AudioSystem();

				virtual void init();
				virtual void update(float);

				Mix_Music* music;


		};
	}
}

#endif
