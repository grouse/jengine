// Copyright (c) 2014 Jesper "Grouse" Stefansson. All rights reserved.

#ifndef LEVEL_H
#define LEVEL_H

#include "core/entity.h"
#include "core/component.h"
#include "core/game_objects.h"

#include "components/collision.h"
#include "components/damage.h"
#include "components/health.h"
#include "components/life_time.h"
#include "components/shape.h"
#include "components/texture.h"
#include "components/velocity.h"

namespace JEngine {
	namespace Core {
		
		class Level {
		public:
			static void load(const char*, Core::GameObjects*);
		};
	}
}

#endif
