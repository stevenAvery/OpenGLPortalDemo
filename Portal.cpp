
#include "Portal.h"

Portal::Portal() {
	this->exitPos = glm::vec3(0.0, 0.0, 0.0);
	this->exitForward = glm::vec3(-1.0f, 0.0f, 0.0f);
	this->enterForward = glm::vec3(-1.0f, 0.0f, 0.0f);
	this->x1 = 0.0;
	this->z1 = 0.0;
	this->x2 = 0.0;
	this->z2 = 0.0;
}

glm::vec3 Portal::getExitPos() {
	return this->exitPos;
}

void Portal::setExitPos(glm::vec3 exitPos) {
	this->exitPos = exitPos;
}

glm::vec3 Portal::getExitForward() {
	return this->exitForward;
}

void Portal::setExitForward(glm::vec3 exitForward) {
	this->exitForward = exitForward;
}

glm::vec3 Portal::getEnterForward() {
	return this->enterForward;
}

void Portal::setEnterForward(glm::vec3 enterForward) {
	this->enterForward = enterForward;
}

glm::vec3 Portal::getDeltaPos() {
	return (this->exitPos - this->enterPos);
}
