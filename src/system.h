#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <list>

#include "entity.h"
#include "component.h"
#include "game_objects.h"

namespace JEngine {
	class System {
		public:
			System(GameObjects*);
			virtual ~System();

			virtual void update(float);

		protected:
			GameObjects* objects;
			

	};
}

#endif
