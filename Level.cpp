
#include "Level.h"
#include "VAO.h"

void Level::load(GLuint program, int levelNumber) {
	if(levelNumber == 1) {
		VAO room0VAO;
		VAO room1VAO;
		VAO port0VAO;
		VAO port1VAO;

		// load obj models
		room0VAO.loadObj(program, (char *)"models/room0.obj");
		room1VAO.loadObj(program, (char *)"models/room1.obj");
		port0VAO.loadObj(program, (char *)"models/portal0.obj");
		port1VAO.loadObj(program, (char *)"models/portal1.obj");

		// add entities
		entities.push_back(Entity(room0VAO, glm::vec3(0.0, 0.0, 0.0)));
		entities.push_back(Entity(room1VAO, glm::vec3(0.0, 0.0, 50.0)));

		// add portals
		Portal portal0;
		portal0.entity.setPos(glm::vec3(0.0, 0.0, 0.0));
		portal0.entity.setVAO(port0VAO);
		portal0.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal0.setExitPos(glm::vec3(-2.0, 0.0, 50.0));
		portal0.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal0.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal0.x1 = 2.0;
		portal0.z1 = -2.0;
		portal0.x2 = 3.0;
		portal0.z2 = 2.0;
		portals.push_back(portal0);

		Portal portal1;
		portal1.entity.setPos(glm::vec3(0.0, 0.0, 0.0));
		portal1.entity.setVAO(port1VAO);
		portal1.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal1.setExitPos(glm::vec3(-2.0, 0.0, 50.0));
		portal1.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.x1 = 2.0;
		portal1.z1 = -2.0;
		portal1.x2 = 3.0;
		portal1.z2 = 2.0;
		portals.push_back(portal1);

		// wall collision
		// room 0
		wallCollision.push_back(Box(-3.0, -3.0, -2.0, -2.0));
		wallCollision.push_back(Box( 2.0, -3.0,  3.0, -2.0));
		wallCollision.push_back(Box( 2.0,  2.0,  3.0,  3.0));
		wallCollision.push_back(Box(-3.0,  2.0, -2.0,  3.0));
		wallCollision.push_back(Box(-16.0, -17.0,  16.0, -16.0));
		wallCollision.push_back(Box(-16.0,  16.0,  16.0,  17.0));
		wallCollision.push_back(Box(-17.0, -16.0, -16.0,  16.0));
		wallCollision.push_back(Box( 16.0, -16.0,  17.0,  16.0));

		// room 1

	}
}
