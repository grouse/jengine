// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {
		class Audio : public Core::Component {
			public:
				Audio(const char*, void (*)(Audio*));
				virtual ~Audio();

				virtual bool canAttach(Core::Entity&);
				
				const char* file;
				Mix_Music* sound;
				
				void (*callback)(Audio*);

		};
	}
}


#endif
