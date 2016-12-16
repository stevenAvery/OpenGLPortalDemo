
#ifndef ENTITY_H
#define ENTITY_H

#include "VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity {
private:
	VAO vao;
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 colour;

public:
	Entity();
	Entity(VAO vao, glm::vec3 pos);
	void setPos(glm::vec3 pos);
	glm::vec3 getPos();
	void setScale(glm::vec3 scale);
	glm::vec3 getScale();
	void setVAO(VAO vao);
	VAO getVAO();
	void setColour(glm::vec3 colour);
	glm::vec3 getColour();
	glm::mat4 getModelMatrix();
};

#endif
