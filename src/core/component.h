// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: component.h
// author: Jesper Stefansson
//
// Contains the Component class which is the base class for
// all the different components. 
// Component contains the different Component ID's available, e.g.
// the Velocity's component id is 0. These are globally available
// as static constant integers.
//
// Also defines the canAttach function which should be used to check
// whether an entity meets a component's dependencies.
#ifndef COMPONENT_H
#define COMPONENT_H

namespace JEngine {
	namespace Core {
		class Entity;

		// See file comments for class details
		class Component {
			public:
				// Initialise the component type variable
				Component(unsigned int id) : type(id) {};
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

				
				const unsigned int type; 	// Component id, set by child class constructor 
				Entity* owner; 				// The entity to which the component is attached

				// Checks whether the entity meets the component's dependencies for attachment
				virtual bool canAttach(Entity&) = 0;
		};
	}
}

#endif
