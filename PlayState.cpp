
#include "PlayState.h"
#include "Level.h"

#define FOV 45.0f
#define NEAR_CLIP 0.01f
#define FAR_CLIP 50.0f
#define SENSITIVITY 0.8f

GLuint program;
glm::mat4 projection;

Camera camera;
Keyboard keys;
Level level;
int width = 0;
int height = 0;

void PlayState::enter() {
	glEnable(GL_STENCIL_TEST);
	glClearStencil(0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutSetCursor(GLUT_CURSOR_NONE);

	int vs = buildShader(GL_VERTEX_SHADER,   (char *)"shaders/normals2.vs");
	int fs = buildShader(GL_FRAGMENT_SHADER, (char *)"shaders/normals2.fs");
	program = buildProgram(vs, fs, 0);

	// load the level models (as obj), and data
	level.load(program, 1);
	std::cout << "Level loaded: " << std::endl;
	std::cout << "\tNumber of portals: " << level.portals.size() << std::endl;

	// set player position
	player.setPos(glm::vec3(8.0, 4.0, 8.0));
	player.setForward(glm::vec3(-1.0, 0.0, -1.0));
	player.setUp(glm::vec3(0.0, 1.0, 0.0));
}

void PlayState::leave() {

}

void PlayState::update() {
	// update mouse
	int deltaMovex = mouse.getx() - width/2;
	float deltaMovey = mouse.gety() - height/2;
	float mouseMoveRatiox = (float)deltaMovex/width;
	float mouseMoveRatioy = (float)deltaMovey/height;

	if(mouse.getx() != 0 && mouse.getx() != 0) {
		player.rotateRight(mouseMoveRatiox*SENSITIVITY);
		player.rotateUp(-mouseMoveRatioy*SENSITIVITY);
	}
	mouse.warp(width/2, height/2);


	// User input for player
	if(keys.isDown('a'))
		player.moveTowards(-player.getRight());
	if(keys.isDown('d'))
		player.moveTowards(player.getRight());
	if(keys.isDown('w'))
		player.moveTowards(player.getForwardXZ());
	if(keys.isDown('s'))
		player.moveTowards(-player.getForwardXZ());
	if(keys.isDown('j'))
		player.rotateRight(-player.ROT_SPEED);
	if(keys.isDown('l'))
		player.rotateRight(player.ROT_SPEED);
	if(keys.isDown('i'))
		player.rotateUp(player.ROT_SPEED);
	if(keys.isDown('k'))
		player.rotateUp(-player.ROT_SPEED);

	// player step one frame
	glm::vec3 pos0 = player.getPos();
	player.step(1000/60);
	glm::vec3 pos = player.getPos();
	glm::vec3 vel = player.getVel();

	// portal collision
	for(int i = 0; i < level.portals.size(); i++) {
		if(pos.x > level.portals[i].x1 && pos.x < level.portals[i].x2 &&
		   pos.z > level.portals[i].z1 && pos.z < level.portals[i].z2) {
			// only teleport if the user is looking in the same direction as the portal
			if(acos(glm::dot(player.getForward(), level.portals[i].getEnterForward())) < 3.14/2)
				pos += level.portals[i].getDeltaPos();
		}
	}

	// wall collision
	for(int i = 0; i < level.wallCollision.size(); i++) {
		// x component
		if(pos.x+player.RAD > level.wallCollision[i].x1 && pos.x-player.RAD < level.wallCollision[i].x2 &&
		   pos.z > level.wallCollision[i].z1 && pos.z < level.wallCollision[i].z2) {
			vel.x = 0.0;
			pos.x = pos0.x;
		}
		// z component
		if(pos.x > level.wallCollision[i].x1 && pos.x < level.wallCollision[i].x2 &&
		   pos.z+player.RAD > level.wallCollision[i].z1 && pos.z-player.RAD < level.wallCollision[i].z2) {
			vel.z = 0.0;
			pos.z = pos0.z;
		}
	}

	player.setPos(pos);
	player.setVel(vel);
}

void renderFromView(glm::mat4 view) {
	glUniformMatrix4fv(glGetUniformLocation(program, "view"),
		1, 0, glm::value_ptr(view));

	// draw each entity
	for(int i = 0; i < level.entities.size(); ++i) {
		glUniformMatrix4fv(glGetUniformLocation(program, "model"),
			1, 0, glm::value_ptr(level.entities[i].getModelMatrix()));
		glUniform3fv(glGetUniformLocation(program, "modelColour"),
			1, glm::value_ptr(level.entities[i].getColour()));

		glBindVertexArray(level.entities[i].getVAO().getVaoID());
		glDrawElements(GL_TRIANGLES, level.entities[i].getVAO().getTriangles()*3, GL_UNSIGNED_INT, NULL);
	}
}

void PlayState::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glUseProgram(program);

	// Update projection matrix
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"),
		1, 0, glm::value_ptr(projection));

	// render from player view
	glDisable(GL_STENCIL_TEST);
	camera.setPosition(player.getPos());
	camera.setForward(player.getForward());
	camera.setUp(player.getUp());
	renderFromView(camera.render());

	// draw each of the portals
	for(int i = 0; i < level.portals.size(); i++) {
		// set initial player view
		camera.setPosition(player.getPos());
		camera.setForward(player.getForward());
		camera.setUp(player.getUp());

		// disable colour and depth buffer, enable stencil buffer
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_STENCIL_TEST);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		glStencilFunc(GL_NEVER, 1, 0xFF);
		glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);

		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);

		// draw the portal
		glUniformMatrix4fv(glGetUniformLocation(program, "view"),
			1, 0, glm::value_ptr(camera.render()));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"),
			1, 0, glm::value_ptr(level.portals[i].entity.getModelMatrix()));
		glUniform3fv(glGetUniformLocation(program, "modelColour"),
			1, glm::value_ptr(glm::vec3(1.0, 0.0, 1.0)));

		glBindVertexArray(level.portals[i].entity.getVAO().getVaoID());
		glDrawElements(GL_TRIANGLES, level.portals[i].entity.getVAO().getTriangles()*3, GL_UNSIGNED_INT, NULL);

		// enable colour and depth buffer, disable stencil buffer
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glStencilMask(0x00);
		glStencilFunc(GL_LEQUAL, 1, 0xFF); // where the stencil buffer is one

		// clip the near plane properly (see Rendering a Single Portal in: https://th0mas.nl/2013/05/19/rendering-recursive-portals-with-opengl/)
		camera.setPosition(player.getPos() + level.portals[i].getDeltaPos());
		camera.setForward(player.getForward());
		camera.setUp(player.getUp());
		renderFromView(camera.render());
	}

	glutSwapBuffers();
}

void PlayState::changeSize(int w, int h) {
	if (h == 0) h = 1; // Prevent a divide by zero, when window is too short

	width = w;
	height = h;

	float ratio = 1.0 * w / h;
	glViewport(0, 0, w, h);
	projection = glm::perspective(FOV, ratio, NEAR_CLIP, FAR_CLIP);

	// warp the mouse back to the middle
	mouse.warp(width/2, height/2);
}

void PlayState::keyboardDown(unsigned char key, int x, int y) {
	// Exit on Esc
	if(key == 27)
		glutLeaveMainLoop();
	if(key == 'q') {
		std::cout << "pos: " << player.getPos().x << ", " << player.getPos().y << ", " << player.getPos().z << std::endl;
	}
}

void PlayState::keyboardUp(unsigned char key, int x, int y) {

}

void PlayState::mousePress(int button, int state, int x, int y) {

}

void PlayState::mouseMove(int x, int y) {

}
