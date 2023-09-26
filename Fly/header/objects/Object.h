#pragma once

#include <glm/glm.hpp>

class Object
{
public:
	Object(glm::vec3 position, glm::vec3 direction) { this->position = position; this->direction = direction; }
	virtual ~Object() = default;

	glm::vec3 getPosition() { return position; }
	glm::vec3 getDirection() { return direction; }
	void setPosition(glm::vec3 position) { this->position = position; }
	void setDirection(glm::vec3 position) { this->direction = direction; }

protected:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 direction = glm::vec3(1, 0, 0);
};