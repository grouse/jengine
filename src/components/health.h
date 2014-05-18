#ifndef HEALTH_H
#define HEALTH_H

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	class Health : public Component {
		public:
			Health(float);
			virtual ~Health();

			virtual bool canAttach(Entity&);
			
			float health;
	};
}

#endif
