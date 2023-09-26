#include "Object.h"

Object::Object(glm::vec3 position, glm::vec3 direction)
{
	// @Joris: Ik moet hier "this" gebruiken anders wordt het veld niet geupdate.. Idem setDirection... 
	this->position = position;
	this->direction = direction;
}

glm::vec3 Object::getPosition()
{
	return position;
}

glm::vec3 Object::getDirection()
{
	return direction;
}

void Object::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Object::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}
