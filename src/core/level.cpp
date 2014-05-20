#include "level.h"


#include <cstdio>

#include <sstream>
#include <string>
#include <iostream>

namespace JEngine {
	namespace Core {
		static void load_tex(Entity*, GameObjects*, std::string*);
		static void load_vel(Entity*, GameObjects*, std::string*);
		static void load_col(Entity*, GameObjects*, std::string*);
		static void load_dmg(Entity*, GameObjects*, std::string*);
		static void load_hp(Entity*, GameObjects*, std::string*);
		static void load_lfe(Entity*, GameObjects*, std::string*);
		static void load_shp(Entity*, GameObjects*, std::string*);

		static void (*load_cmp[])(Entity*, GameObjects*, std::string*) = {
			load_vel,
			load_shp,
			load_tex,
			load_col,
			load_lfe,
			load_dmg,
			load_hp
		};

		void Level::load(const char* filename, Core::GameObjects* objects) {
			std::cout << "Loading entities from: " << filename << "\n";
			
			std::string test = "50 50 0 1000 1000 400";

			std::cout << "test variable pre velocity: " << test << "\n";
			load_cmp[Component::VELOCITY](0, 0, &test);

			std::cout << "test variable post velocity: " << test << "\n";
		}
		
		void load_tex(Entity* e, GameObjects* o, std::string* data) {}

		void load_vel(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);
			std::string rest;

			float x, y, z;
			float accel, deaccel;
			float max_speed;

			s >> x >> y >> z >> accel >> deaccel >> max_speed >> rest;
			*data = rest;
		}

		void load_col(Entity* e, GameObjects* o, std::string* data) {}

		void load_dmg(Entity* e, GameObjects* o, std::string* data) {}

		void load_hp(Entity* e, GameObjects* o, std::string* data) {}

		void load_lfe(Entity* e, GameObjects* o, std::string* data) {}

		void load_shp(Entity* e, GameObjects* o, std::string* data) {}
	}
}
