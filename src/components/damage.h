// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: damage.h
// author: Jesper Stefansson
//
//

#ifndef DAMAGE_H
#define DAMAGE_H

#include "core/entity.h"
#include "core/component.h"

namespace JEngine {
	namespace Components {
		class Damage : public Core::Component {
			public:
				Damage(float);
				virtual ~Damage();

				virtual bool canAttach(Core::Entity&);

				float damage;
		};
	}
}

#endif
