#include "behaviors/FollowBehavior.h"

void FollowBehavior::think(long timeDeltaMsec, long long timeAbsoluteMsec)
{
	if (followTarget == nullptr || behaviorTarget == nullptr)
	{
		return;
	}

	glm::vec3 direction = followTarget->getDirection();
	glm::vec3 position = followTarget->getPosition();

	// Find horizontal offset by getting the cross product from the target direction and up.
	glm::vec3 cross = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
	glm::vec3 horizontal = position + cross * offset.x;

	// Find final destination by inverting the direction, multiply with offset component and adding to position.
	glm::vec3 target = horizontal + (-direction * offset.z);

	behaviorTarget->setDestination(target);
}
