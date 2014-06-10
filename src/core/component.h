// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef COMPONENT_H
#define COMPONENT_H

namespace JEngine {
	namespace Core {
		class Entity;

		class Component {
			public:
				Component(unsigned int t) : type(t) {};
				virtual ~Component() {}

				static const unsigned int 
					VELOCITY = 0,
					SHAPE = 1,
					TEXTURE = 2,
					COLLISION = 3,
					LIFETIME = 4,
					DAMAGE = 5,
					HEALTH = 6,
					AUDIO = 7,
					NUM_TYPES = 8;

				
				const unsigned int type;
				Entity* owner;

				virtual bool canAttach(Entity&) = 0;
		};
	}
}

#endif
