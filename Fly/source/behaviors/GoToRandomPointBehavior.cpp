#include "behaviors/GoToRandomPointBehavior.h"
#include <iostream>

void GoToRandomPointBehavior::think(long timeDeltaMsec, long long timeAbsoluteMsec)
{
	if (timeAbsoluteMsec - lastTick > timeBetweenDirectionChanges)
	{
		float destX = (float)(rand() % (int)fieldSize.x);
		float destZ = (float)(rand() % (int)fieldSize.y);
		glm::vec3 destination = glm::vec3(destX, 3, destZ);
		std::cout << "\nBird flies to: " << destination.x << ", " << destination.y;
		behaviorTarget->setDestination(destination);
		lastTick = timeAbsoluteMsec;
	}
}
