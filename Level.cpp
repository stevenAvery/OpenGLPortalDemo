
#include "Level.h"
#include "VAO.h"

void Level::load(GLuint program, int levelNumber) {
	if(levelNumber == 1) {
		VAO room0VAO, room1VAO, room2VAO, room2MonkeyVAO;
		VAO port0VAO, port1VAO, port2VAO;

		// load obj models
		room0VAO.loadObj(program, (char *)"models/room0a.obj");
		room1VAO.loadObj(program, (char *)"models/room1a.obj");
		room2VAO.loadObj(program, (char *)"models/room2a.obj");
		room2MonkeyVAO.loadObj(program, (char *)"models/room2Monkey.obj");
		port0VAO.loadObj(program, (char *)"models/portal0a.obj");
		port1VAO.loadObj(program, (char *)"models/portal1a.obj");
		port2VAO.loadObj(program, (char *)"models/portal2.obj");

		// add entities
		entities.push_back(Entity(room0VAO, glm::vec3(0.0, 0.0, 0.0)));
		entities.push_back(Entity(room1VAO, glm::vec3(50.0, 0.0, -50.0)));
		entities.push_back(Entity(room2VAO, glm::vec3(50.0, 0.0, 50.0)));
		entities.push_back(Entity(room2MonkeyVAO, glm::vec3(50.0, 0.0, 50.0)));

		// add portals
		Portal portal0;
		portal0.entity.setPos(glm::vec3(0.0, 0.0, 0.0));
		portal0.entity.setVAO(port0VAO);
		portal0.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal0.setExitPos(glm::vec3(48.0, 0.0, -50.0));
		portal0.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal0.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal0.x1 = 2.0;
		portal0.z1 = -2.0;
		portal0.x2 = 3.0;
		portal0.z2 = 2.0;
		portals.push_back(portal0);

		Portal portal1;
		portal1.entity.setPos(glm::vec3(50.0, 0.0, -50.0));
		portal1.entity.setVAO(port1VAO);
		portal1.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal1.setExitPos(glm::vec3(8.0, 0.0, 0.0));
		portal1.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.x1 = -7.0;
		portal1.z1 = 48.0;
		portal1.x2 = -6.0;
		portal1.z2 = 52.0;
		portals.push_back(portal1);

		Portal portal2;
		portal2.entity.setPos(glm::vec3(0.0, 0.0, 0.0));
		portal2.entity.setVAO(port2VAO);
		portal2.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal2.setExitPos(glm::vec3(37.0, 0.0, 50.0));
		portal2.setExitForward(glm::vec3(1.0f, 0.0f, 0.0f));
		portal2.setEnterForward(glm::vec3(1.0f, 0.0f, 0.0f));
		portal2.x1 = -3.0;
		portal2.z1 = -2.0;
		portal2.x2 = -2.0;
		portal2.z2 = 2.0;
		portals.push_back(portal2);

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
		wallCollision.push_back(Box(-8.0, 47.0, -7.0, 53.0));
		wallCollision.push_back(Box(-8.0, 47.0,  8.0, 48.0));
		wallCollision.push_back(Box(-8.0, 52.0,  8.0, 53.0));
		wallCollision.push_back(Box( 4.0, 47.0,  5.0, 53.0));
	}
}
