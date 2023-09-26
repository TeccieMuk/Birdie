#include "camera/Follow3rdPersonCamera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

void Follow3rdPersonCamera::setTarget(Object& objectToFollow)
{
	target = objectToFollow;
	lookingDirection = objectToFollow.getDirection();
}

glm::vec3 Follow3rdPersonCamera::getPosition()
{
	return lastPosition;
}

glm::mat4 Follow3rdPersonCamera::getView(float time, float timeDelta)
{
	glm::vec3 targetPosition = target.getPosition();
	glm::vec3 targetDirection = target.getDirection();

	// Move own looking direction closer to target direction
	glm::vec3 cross = glm::cross(targetDirection, lookingDirection);
	float dotReversed = (1 - glm::dot(targetDirection, lookingDirection)) * 6;
	float rotation = 0;
	if (cross.y < 0)
	{
		rotation += cameraRotateSpeed * timeDelta * dotReversed;
	}
	else if (cross.y > 0)
	{
		rotation -= cameraRotateSpeed * timeDelta * dotReversed;
	}

	glm::mat4 rotateToTarget = glm::mat4(1.0f);
	rotateToTarget = glm::rotate(rotateToTarget, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 rotationVector = glm::vec4(lookingDirection.x, lookingDirection.y, lookingDirection.z, 0);
	lookingDirection = normalize(rotateToTarget * rotationVector);

	lastPosition = targetPosition + targetDirection * -cameraDistance;
	lastPosition.y += 1;
	glm::vec3 lookAtPosition = lastPosition + lookingDirection;

	return glm::lookAt(lastPosition, lookAtPosition, glm::vec3(0,1,0));
}