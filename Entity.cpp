
#include "Entity.h"

Entity::Entity() {
	this->pos = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
	this->colour = glm::vec3(0.75, 0.75, 0.75);
}

Entity::Entity(VAO vao, glm::vec3 pos) {
	this->pos = pos;
	this->scale = glm::vec3(1.0, 1.0, 1.0);
	this->colour = glm::vec3(0.75, 0.75, 0.75);
	this->vao = vao;
}


void Entity::setPos(glm::vec3 pos) {
	this->pos = pos;
}

glm::vec3 Entity::getPos() {
	return pos;
}

void Entity::setScale(glm::vec3 scale) {
	this->scale = scale;
}

glm::vec3 Entity::getScale() {
	return scale;
}

void Entity::setVAO(VAO vao) {
	this->vao = vao;
}

VAO Entity::getVAO() {
	return vao;
}

void Entity::setColour(glm::vec3 colour) {
	this->colour = colour;
}

glm::vec3 Entity::getColour() {
	return colour;
}

glm::mat4 Entity::getModelMatrix() {
	return glm::translate(glm::scale(glm::mat4(1.0), scale), pos);
}
