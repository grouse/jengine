#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <list>

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"

namespace JEngine {
	namespace Core {
		class System {
			public:
				System(GameObjects*);
				virtual ~System();

				virtual void init() = 0;
				virtual void update(float) = 0;

			protected:
				bool initialised = false;
				GameObjects* objects;
				

		};
	}
}

#endif
