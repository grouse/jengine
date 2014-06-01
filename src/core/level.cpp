#include "level.h"


#include <cstdio>

#include <sstream>
#include <string>
#include <iostream>

namespace JEngine {
	namespace Core {
		static void load_tex(Entity*, GameObjects*, std::stringstream&);
		static void load_vel(Entity*, GameObjects*, std::stringstream&);
		static void load_col(Entity*, GameObjects*, std::stringstream&);
		static void load_dmg(Entity*, GameObjects*, std::stringstream&);
		static void load_hp(Entity*, GameObjects*, std::stringstream&);
		static void load_lfe(Entity*, GameObjects*, std::stringstream&);
		static void load_shp(Entity*, GameObjects*, std::stringstream&);

		static void (*load_cmp[])(Entity*, GameObjects*, std::stringstream&) = {
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
			
			std::string velocity("0 50 50 0 1000 1000 400");
			std::string shape("1 12 -16 -16 0 16 -16 0 16 16 0 -16 16 0");
			std::string lifetime("4 300");
			std::string damage("5 300");
			std::string health("6 300");
			std::string texture("2 assets/ship.png");

			std::string data = lifetime + " " + velocity + " " +  damage + " " + health + " " + texture + " " + shape;

				
			std::stringstream s;
			s << data <<  '\n';

			int cmp;
			s >> cmp;

			while (!s.eof()) {
				load_cmp[cmp](0, 0, s);
				s >> cmp;
			}
		}
		
		void load_tex(Entity* e, GameObjects* o, std::stringstream& s) {
			std::string filename;

			s >> filename;
			std::cout << "Loaded texture component!\n\tfilename: " << filename << "\n\n";
		}

		void load_vel(Entity* e, GameObjects* o, std::stringstream& s) {
			float x, y, z;
			float accel, deaccel;
			float max_speed;

			s >> x >> y >> z >> accel >> deaccel >> max_speed;

			std::cout << "Loaded velocity component:\n";
			std::cout << "\tvector: (" << x << ", " << y << ", " << z << ")\n";
			std::cout << "\tacceleration: " << accel << "\n";
			std::cout << "\tdeacceleration: " << deaccel << "\n";
			std::cout << "\tmax_speed: " << max_speed << "\n\n";
		}

		void load_col(Entity* e, GameObjects* o, std::stringstream& s) {}

		void load_dmg(Entity* e, GameObjects* o, std::stringstream& s) {
			float damage;

			s >> damage;
			std::cout << "Loaded damage component!\n\tdamage: " << damage << "\n\n";
		}

		void load_hp(Entity* e, GameObjects* o, std::stringstream& s) {
			float health;

			s >> health;
			std::cout << "Loaded health component!\n\thealth: " << health << "\n\n";
		}

		void load_lfe(Entity* e, GameObjects* o, std::stringstream& s) {
			int lifetime;

			s >> lifetime;;
			std::cout << "Loaded life_time component!\n\tlifetime: " << lifetime << "\n\n";
		}

		void load_shp(Entity* e, GameObjects* o, std::stringstream& s) {
			unsigned int n;

			s >> n;

			float vertices[n];
			for (unsigned int i = 0; i < n; i++) 
				s >> vertices[i];
			
			std::cout << "Loaded shape component!\n";
			std::cout << "\tnbr vertices: " << n/3 << "\n\tvertices: {\n";
			for (unsigned int i = 0; i < n/3; i++) {
				std::cout << "\t\t(" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << ")\n";
			}
			std::cout << "\t}\n\n";
		
		}
	}
}
