// Copyright (c) 2014 Jesper Stefansson. All rights reserved.
//
// file: level.cpp
// author: Jesper Stefansson

#include "level.h"


#include <cstdio>

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

// Component loaders
static void load_tex(Entity*, GameObjects*, std::stringstream&); // Texture loader
static void load_vel(Entity*, GameObjects*, std::stringstream&); // Velocity loader
static void load_col(Entity*, GameObjects*, std::stringstream&); // Collision loader
static void load_dmg(Entity*, GameObjects*, std::stringstream&); // Damage loader
static void load_hp(Entity*, GameObjects*, std::stringstream&);  // Health loader
static void load_lfe(Entity*, GameObjects*, std::stringstream&); // LifeTime loader
static void load_shp(Entity*, GameObjects*, std::stringstream&); // Shape loader

// Array of function pointers to above component loaders
// indexed by Component ID for calling by index ID
static void (*load_cmp[])(Entity*, GameObjects*, std::stringstream&) = {
	load_vel,
	load_shp,
	load_tex,
	load_col,
	load_lfe,
	load_dmg,
	load_hp
};

void Level::load(const char* filename, GameObjects* objects) {
	std::cout << "Loading entities from: " << filename << "\n";
	
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	int cmp;
	std::string line;

	// for each line in the file, create a new entity with position provided
	// as the first 3 floats separated by space. 
	// Get next integer as component ID and pass the remaining data to the 
	// component loader.
	std::getline(file, line);
	while (!file.eof()) {
		std::stringstream s(line + '\n');

		float x, y, z; 
		s >> x >> y >> z;

		Entity* e = objects->pushEntity(new Entity(x, y, z));

		s >> cmp;

		// while stream still has input, load component and attach to entity
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
	//objects->attachComponent(e, new Texture(filename.c_str()));

	std::cout << "Loaded texture component!\n\tfilename: " << filename << "\n\n";
}

void load_vel(Entity* e, GameObjects* objects, std::stringstream& s) {
	float x, y, z;
	float accel, deaccel;
	float max_speed;

	s >> x >> y >> z >> accel >> deaccel >> max_speed;
	objects->attachComponent(e, new Velocity(x, y, z, accel, deaccel, max_speed));

	std::cout << "Loaded velocity component:\n";
	std::cout << "\tvector: (" << x << ", " << y << ", " << z << ")\n";
	std::cout << "\tacceleration: " << accel << "\n";
	std::cout << "\tdeacceleration: " << deaccel << "\n";
	std::cout << "\tmax_speed: " << max_speed << "\n\n";
}

void load_col(Entity* e, GameObjects* objects, std::stringstream& s) {
	unsigned int t;
	s >> t;

	Collision* c;
	std::string type;

	switch (t) {
		default:
		case 0:
			c = new Collision(CollisionResponse::rigid_body);
			type = "RigidBody";
			break;

		case 1:
			c = new Collision(CollisionResponse::static_body);
			type = "StaticBody";
			break;

		case 2:
			c = new Collision(CollisionResponse::projectile);
			type = "Projectile";
			break;
	}

	objects->attachComponent(e, c);
	std::cout << "Loaded collision component!\n";
	std::cout << "\ttype: " << type << "\n";
}

void load_dmg(Entity* e, GameObjects* objects, std::stringstream& s) {
	float damage;

	s >> damage;
	objects->attachComponent(e, new Damage(damage));

	std::cout << "Loaded damage component!\n\tdamage: " << damage << "\n\n";
}

void load_hp(Entity* e, GameObjects* objects, std::stringstream& s) {
	float health;

	s >> health;
	objects->attachComponent(e, new Health(health));

	std::cout << "Loaded health component!\n\thealth: " << health << "\n\n";
}

void load_lfe(Entity* e, GameObjects* objects, std::stringstream& s) {
	int lifetime;

	s >> lifetime;;
	objects->attachComponent(e, new LifeTime(lifetime));

	std::cout << "Loaded life_time component!\n\tlifetime: " << lifetime << "\n\n";
}

void load_shp(Entity* e, GameObjects* objects, std::stringstream& s) {
	unsigned int n;

	s >> n;
	float vertices[n];

	for (unsigned int i = 0; i < n; i++)
		s >> vertices[i];

	objects->attachComponent(e, new Shape(vertices, n));
	
	std::cout << "Loaded shape component!\n";

}
