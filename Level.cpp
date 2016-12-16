
#include "Level.h"
#include "VAO.h"

void Level::load(GLuint program, int levelNumber) {
	if(levelNumber == 1) {
		VAO room0VAO, room1VAO, room2VAO, room2MonkeyVAO;
		VAO port0VAO, port1VAO, port2VAO, port3VAO;

		// load obj models
		room0VAO.loadObj(program, (char *)"models/room0a.obj");
		room1VAO.loadObj(program, (char *)"models/room1a.obj");
		room2VAO.loadObj(program, (char *)"models/room2a.obj");
		room2MonkeyVAO.loadObj(program, (char *)"models/room2Monkey.obj");
		port0VAO.loadObj(program, (char *)"models/portal0a.obj");
		port1VAO.loadObj(program, (char *)"models/portal1.obj");
		port2VAO.loadObj(program, (char *)"models/portal2.obj");
		port3VAO.loadObj(program, (char *)"models/portal3.obj");

		// add entities
		entities.push_back(Entity(room0VAO, glm::vec3(0.0, 0.0, 0.0)));
		entities.push_back(Entity(room1VAO, glm::vec3(100.0, 0.0, -100.0)));
		entities.push_back(Entity(room2VAO, glm::vec3(100.0, 0.0, 100.0)));
		entities.push_back(Entity(room2MonkeyVAO, glm::vec3(100.0, 0.0, 100.0)));

		// add portals
		Portal portal0;
		portal0.entity.setPos(glm::vec3(0.0, 0.0, 0.0));
		portal0.entity.setVAO(port0VAO);
		portal0.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal0.setExitPos(glm::vec3(98.0, 0.0, -100.0));
		portal0.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal0.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal0.x1 = 2.0;
		portal0.z1 = -2.0;
		portal0.x2 = 3.0;
		portal0.z2 = 2.0;
		portals.push_back(portal0);

/*
		Portal portal1;
		portal1.entity.setPos(glm::vec3(100.0, 0.0, -100.0));
		portal1.entity.setVAO(port1VAO);
		portal1.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal1.setExitPos(glm::vec3(8.0, 0.0, 0.0));
		portal1.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.x1 = -7.0;
		portal1.z1 = 48.0;
		portal1.x2 = -6.0;
		portal1.z2 = 52.0;
		portals.push_back(portal1); */

		Portal portal1;
		portal1.entity.setPos(glm::vec3(100.0, 0.0, -100.0));
		portal1.entity.setVAO(port1VAO);
		portal1.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal1.setExitPos(glm::vec3(-98.0, 0.0, 100.0));
		portal1.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal1.setEnterForward(glm::vec3(1.0f, 0.0f, 0.0f));
		portal1.x1 = 102.0;
		portal1.z1 = -102.0;
		portal1.x2 = 103.0;
		portal1.z2 = -98.0;
		portals.push_back(portal1);

		Portal portal2;
		portal2.entity.setPos(glm::vec3(0.0, 0.0, 0.0));
		portal2.entity.setVAO(port2VAO);
		portal2.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal2.setExitPos(glm::vec3(87.0, 0.0, 100.0));
		portal2.setExitForward(glm::vec3(1.0f, 0.0f, 0.0f));
		portal2.setEnterForward(glm::vec3(1.0f, 0.0f, 0.0f));
		portal2.x1 = -3.0;
		portal2.z1 = -2.0;
		portal2.x2 = -2.0;
		portal2.z2 = 2.0;
		portals.push_back(portal2);

		Portal portal3;
		portal3.entity.setPos(glm::vec3(100.0, 0.0, 100.0));
		portal3.entity.setVAO(port3VAO);
		portal3.enterPos = glm::vec3(0.0, 0.0, 0.0);
		portal3.setExitPos(glm::vec3(-74.0, 0.0, -100.0));
		portal3.setExitForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal3.setEnterForward(glm::vec3(-1.0f, 0.0f, 0.0f));
		portal3.x1 = 83.0;
		portal3.z1 = 98.0;
		portal3.x2 = 84.0;
		portal3.z2 = 102.0;
		portals.push_back(portal3);


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
		wallCollision.push_back(Box(81,  -102, 82,  -98));
		//wallCollision.push_back(Box(102, -102, 103, -98));
		wallCollision.push_back(Box(82,  -103, 102, -102));
		wallCollision.push_back(Box(82,  -98,  102, -97));

		// room 2
		wallCollision.push_back(Box(84,  97,  85,  98));
		wallCollision.push_back(Box(84,  102, 85,  103));
		wallCollision.push_back(Box(83,  102, 84,  116));
		wallCollision.push_back(Box(83,  83,  84,  98));
		wallCollision.push_back(Box(116, 84,  117, 116));
		wallCollision.push_back(Box(84,  83,  116, 84));
		wallCollision.push_back(Box(84,  116, 116, 117));
	}
}
