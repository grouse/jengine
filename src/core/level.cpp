#include "level.h"


#include <cstdio>

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

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
			
			std::ifstream file;
			file.open(filename, std::ifstream::in);

			int cmp;
			std::string line;

			std::getline(file, line);
			while (!file.eof()) {
				std::stringstream s(line + '\n');

				float x, y, z;
				s >> x >> y >> z;

				Entity* e = objects->pushEntity(new Entity(x, y, z));

				s >> cmp;

				while (!s.eof()) {
					load_cmp[cmp](e, objects, s);
					s >> cmp;
				}
				
				std::getline(file, line);
			}
		}
		
		void load_tex(Entity* e, GameObjects* objects, std::stringstream& s) {
			std::string filename;

			s >> filename;
			objects->attachComponent(e, new Components::Texture(filename.c_str()));

			std::cout << "Loaded texture component!\n\tfilename: " << filename << "\n\n";
		}

		void load_vel(Entity* e, GameObjects* objects, std::stringstream& s) {
			float x, y, z;
			float accel, deaccel;
			float max_speed;

			s >> x >> y >> z >> accel >> deaccel >> max_speed;
			objects->attachComponent(e, new Components::Velocity(x, y, z, accel, deaccel, max_speed));

			std::cout << "Loaded velocity component:\n";
			std::cout << "\tvector: (" << x << ", " << y << ", " << z << ")\n";
			std::cout << "\tacceleration: " << accel << "\n";
			std::cout << "\tdeacceleration: " << deaccel << "\n";
			std::cout << "\tmax_speed: " << max_speed << "\n\n";
		}

		void load_col(Entity* e, GameObjects* objects, std::stringstream& s) {}

		void load_dmg(Entity* e, GameObjects* objects, std::stringstream& s) {
			float damage;

			s >> damage;
			objects->attachComponent(e, new Components::Damage(damage));

			std::cout << "Loaded damage component!\n\tdamage: " << damage << "\n\n";
		}

		void load_hp(Entity* e, GameObjects* objects, std::stringstream& s) {
			float health;

			s >> health;
			objects->attachComponent(e, new Components::Health(health));

			std::cout << "Loaded health component!\n\thealth: " << health << "\n\n";
		}

		void load_lfe(Entity* e, GameObjects* objects, std::stringstream& s) {
			int lifetime;

			s >> lifetime;;
			objects->attachComponent(e, new Components::LifeTime(lifetime));

			std::cout << "Loaded life_time component!\n\tlifetime: " << lifetime << "\n\n";
		}

		void load_shp(Entity* e, GameObjects* objects, std::stringstream& s) {
			unsigned int n;

			s >> n;

			float vertices[n];
			for (unsigned int i = 0; i < n; i++) 
				s >> vertices[i];

			objects->attachComponent(e, new Components::Shape(vertices, n));
			
			std::cout << "Loaded shape component!\n";
			std::cout << "\tnbr vertices: " << n/3 << "\n\tvertices: {";
			for (unsigned int i = 0; i < n; i++)
				std::cout << vertices[i] << ", ";
			std::cout << "}\n";
		
		}
	}
}
