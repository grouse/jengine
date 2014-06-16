// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: audio_system.h
// author: Jesper Stefansson
//
// Contains the AudioSystem which handles all sound effects
// and music tracks playing in the game. Currently only 
// supports playing background music

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "core/system.h"
#include "core/engine.h"
#include "core/game_objects.h"

namespace JEngine {
	namespace Systems {

		// See file comments for class details
		class AudioSystem : public Core::System {
			public:
				AudioSystem(Core::Engine*, Core::GameObjects*);
				virtual ~AudioSystem();

				// Initialises the audio controls
				virtual void init();
				virtual void update(float);

				// The background music currently playing
				Mix_Music* music;
		};
	}
}

#endif
