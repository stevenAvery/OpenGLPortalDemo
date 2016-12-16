#ifndef LEVEL_H
#define LEVEL_H

#include "Entity.h"
#include "Portal.h"

class Box {
	public:
		Box(float x1, float z1, float x2, float z2) {
			this->x1 = x1;
			this->z1 = z1;
			this->x2 = x2;
			this->z2 = z2;
		}
		float x1;
		float z1;
		float x2;
		float z2;
};

class Level {
	public:
		std::vector<Entity> entities;
		std::vector<Portal> portals;
		std::vector<Box> wallCollision;

		void load(GLuint program, int levelNumber);
};

#endif
