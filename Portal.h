
#ifndef PORTAL_H
#define PORTAL_H

#include "Entity.h"
#include <glm/glm.hpp>

class Portal {
	private:
		glm::vec3 exitPos;
		glm::vec3 exitForward;
		glm::vec3 enterForward;
	public:
		Entity entity;
		glm::vec3 enterPos;
		float rotateRight;
		float x1, z1, x2, z2;

		Portal();
		glm::vec3 getExitPos();
		void setExitPos(glm::vec3 exitPos);
		glm::vec3 getExitForward();
		void setExitForward(glm::vec3 exitForward);
		glm::vec3 getEnterForward();
		void setEnterForward(glm::vec3 enterForward);
		glm::vec3 getDeltaPos();
};

#endif
