// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "audio_system.h"

#include <iostream>

namespace JEngine {
	namespace Systems {
		AudioSystem::AudioSystem(Core::GameObjects* objects) : Core::System(objects) {


		}

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
