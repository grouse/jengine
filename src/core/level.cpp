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
			
			std::string velocity = "50 50 0 1000 1000 400";
			std::string shape = "12 -16 -16 0 16 -16 0 16 16 0 -16 16 0";

			load_cmp[Component::VELOCITY](0, 0, &velocity);
			load_cmp[Component::SHAPE](0, 0, &shape);
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

			std::cout << "Loaded velocity component:\n";
			std::cout << "vector: (" << x << ", " << y << ", " << z << "), acceleration: " << accel << ", deacceleration: " << deaccel << ", max_speed: " << max_speed << "\n";
		}

		void load_col(Entity* e, GameObjects* o, std::string* data) {}

		void load_dmg(Entity* e, GameObjects* o, std::string* data) {}

		void load_hp(Entity* e, GameObjects* o, std::string* data) {}

		void load_lfe(Entity* e, GameObjects* o, std::string* data) {}

		void load_shp(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);
			std::string rest;

			unsigned int n;
			s >> n;

			float vertices[n];
			for (unsigned int i = 0; i < n; i++) 
				s >> vertices[i];

			s >> rest;
			*data = rest;

			std::cout << "Loaded shape component: \n";
			std::cout << "nbr vertices: " << n/3 << "\nvertices: {\n";
			for (unsigned int i = 0; i < n/3; i++) {
				std::cout << "\t(" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << ")\n";
			}
			std::cout << "}\n";
		
		}
	}
}
