#ifndef LEVEL_H
#define LEVEL_H

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"

namespace JEngine {
	namespace Core {
		
		class Level {
		public:
			static void load(const char*, Core::GameObjects*);
		};
	}
}

#endif
