// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#include "components/audio.h"

namespace JEngine {
	namespace Components {
		
		Audio::Audio(const char* file, void(*callback)(Audio*)) : Core::Component(Core::Component::AUDIO) {
			this->callback = callback;
			this->file = file;
		}

		Audio::~Audio() {}
		bool Audio::canAttach(Core::Entity& e) {
			return true;
		}
	}
}
