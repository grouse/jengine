#ifndef HEALTH_H
#define HEALTH_H

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {
		class Health : public Core::Component {
			public:
				Health(float);
				virtual ~Health();

				virtual bool canAttach(Core::Entity&);
				
				float health;
		};
	}
}

#endif
