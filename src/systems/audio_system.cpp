// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: audio_system.cpp
// author: Jesper Stefansson

#include "audio_system.h"

#include <iostream>

namespace JEngine {
	namespace Systems {
		AudioSystem::AudioSystem(Core::Engine* e, Core::GameObjects* o) :
			Core::System(e, o) {}

		AudioSystem::~AudioSystem() {
			Mix_FreeMusic(music);

			Mix_Quit();
		}

		void AudioSystem::init() {
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				std::cout << "Failed to initialise audio " << Mix_GetError() << "\n";
			}	
			
			music = Mix_LoadMUS("assets/A_Fight.wav");
		}

		void AudioSystem::update(float dt) {
			// For now, just make sure the background music is playing
			if (Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(music, -1);
			} else {
				if (Mix_PausedMusic() == 1) {
					Mix_ResumeMusic();
				}
			}
		}	

	}
}
