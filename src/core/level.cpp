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
			std::string lifetime = "300";
			std::string damage = "300";
			std::string health = "300";
			std::string texture = "assets/ship.png";

			std::string data = velocity + " " + shape + " " + lifetime + " " +  damage + " " + health + " " + texture;

			load_cmp[Component::VELOCITY](0, 0, &data);
			load_cmp[Component::SHAPE](0, 0, &data);
			load_cmp[Component::LIFETIME](0, 0, &data);
			load_cmp[Component::DAMAGE](0, 0, &data);
			load_cmp[Component::HEALTH](0, 0, &data);
			load_cmp[Component::TEXTURE](0, 0, &data);
		}
		
		void load_tex(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);

			std::string filename;
			s >> filename;;
			std::getline(s, *data);

			std::cout << "Loaded texture component!\n\tfilename: " << filename << "\n";
		}

		void load_vel(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);

			float x, y, z;
			float accel, deaccel;
			float max_speed;

			s >> x >> y >> z >> accel >> deaccel >> max_speed;
			std::getline(s, *data);

			std::cout << "Loaded velocity component:\n";
			std::cout << "vector: (" << x << ", " << y << ", " << z << "), acceleration: " << accel << ", deacceleration: " << deaccel << ", max_speed: " << max_speed << "\n";
		}

		void load_col(Entity* e, GameObjects* o, std::string* data) {}

		void load_dmg(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);

			float damage;
			s >> damage;
			std::getline(s, *data);

			std::cout << "Loaded damage component!\n\tdamage: " << damage << "\n";
		}

		void load_hp(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);

			float health;
			s >> health;;
			std::getline(s, *data);

			std::cout << "Loaded health component!\n\thealth: " << health << "\n";
		}

		void load_lfe(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);

			int lifetime;
			s >> lifetime;;
			std::getline(s, *data);

			std::cout << "Loaded life_time component!\n\tlifetime: " << lifetime << "\n";
		}

		void load_shp(Entity* e, GameObjects* o, std::string* data) {
			std::stringstream s(*data);

			unsigned int n;
			s >> n;

			float vertices[n];
			for (unsigned int i = 0; i < n; i++) 
				s >> vertices[i];
			
			std::getline(s, *data);

			std::cout << "Loaded shape component!\n";
			std::cout << "\tnbr vertices: " << n/3 << "\n\tvertices: {\n";
			for (unsigned int i = 0; i < n/3; i++) {
				std::cout << "\t\t(" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << ")\n";
			}
			std::cout << "}\n";
		
		}
	}
}
